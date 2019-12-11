// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatCapsuleComponent.h"
#include "Components/CapsuleComponent.h"
#include "WorldCollision.h"
#include "PrimitiveViewRelevance.h"
#include "PrimitiveSceneProxy.h"
#include "SceneManagement.h"
#include "PhysicsEngine/SphylElem.h"
#include "PhysicsEngine/BodySetup.h"
#include "PrimitiveSceneProxy.h"

UCatCapsuleComponent::UCatCapsuleComponent(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer), Rotation(90.f, 0.f, 0.f)
{
}

// From Engine\Source\Runtime\Engine\Private\Components\CapsuleComponent.cpp
template <EShapeBodySetupHelper UpdateBodySetupAction>
bool InvalidateOrUpdateCatCapsuleBodySetup(UBodySetup*& ShapeBodySetup, bool bUseArchetypeBodySetup, float CapsuleRadius, float CapsuleHalfHeight, const FQuat &Rotation)
{
	check((bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::InvalidateSharingIfStale) || (!bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup));
	check(ShapeBodySetup->AggGeom.SphylElems.Num() == 1);
	FKSphylElem* SE = ShapeBodySetup->AggGeom.SphylElems.GetData();

	const float Length = 2 * FMath::Max(CapsuleHalfHeight - CapsuleRadius, 0.f);	//SphylElem uses height from center of capsule spheres, but UCapsuleComponent uses halfHeight from end of the sphere

	if (UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup)
	{
        FTransform Custom = FTransform::Identity;
        Custom.SetRotation(Rotation);
		SE->SetTransform(Custom);
		SE->Radius = CapsuleRadius;
		SE->Length = Length;
	}
	else
	{
		if(SE->Radius != CapsuleRadius || SE->Length != Length)
		{
			ShapeBodySetup = nullptr;
			bUseArchetypeBodySetup = false;
		}
	}
	
	return bUseArchetypeBodySetup;
}


FPrimitiveSceneProxy* UCatCapsuleComponent::CreateSceneProxy()
{
	/** Represents a UCapsuleComponent to the scene manager. */
	class FDrawCylinderSceneProxy final : public FPrimitiveSceneProxy
	{
	public:
		SIZE_T GetTypeHash() const override
		{
			static size_t UniquePointer;
			return reinterpret_cast<size_t>(&UniquePointer);
		}

		FDrawCylinderSceneProxy(const UCatCapsuleComponent* InComponent)
			: FPrimitiveSceneProxy(InComponent)
			,	Rotation(InComponent->Rotation)
			,	bDrawOnlyIfSelected( InComponent->bDrawOnlyIfSelected )
			,	CapsuleRadius( InComponent->CapsuleRadius )
			,	CapsuleHalfHeight( InComponent->CapsuleHalfHeight )
			,	ShapeColor( InComponent->ShapeColor )
		{
			bWillEverBeLit = false;
		}

		virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
		{
			QUICK_SCOPE_CYCLE_COUNTER( STAT_GetDynamicMeshElements_DrawDynamicElements );

		
			const FMatrix &LocalToWorld = GetLocalToWorld();
			FTransform Custom = FTransform(LocalToWorld);
			FRotator Rot = Rotation + FRotator(Custom.GetRotation());
			Rot.Normalize();
			Custom.SetRotation(FQuat(Rot));
			const FMatrix &LocalToWorldFixed = Custom.ToMatrixWithScale();
			const int32 CapsuleSides =  FMath::Clamp<int32>(CapsuleRadius/4.f, 16, 64);

			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{

				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];
					const FLinearColor DrawCapsuleColor = GetViewSelectionColor(ShapeColor, *View, IsSelected(), IsHovered(), false, IsIndividuallySelected() );

					FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
					DrawWireCapsule( PDI, LocalToWorld.GetOrigin(), LocalToWorldFixed.GetScaledAxis( EAxis::X ), LocalToWorldFixed.GetScaledAxis( EAxis::Y ), LocalToWorldFixed.GetScaledAxis( EAxis::Z ), DrawCapsuleColor, CapsuleRadius, CapsuleHalfHeight, CapsuleSides, SDPG_World );
				}
			}
		}

		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
		{
			const bool bProxyVisible = !bDrawOnlyIfSelected || IsSelected();

			// Should we draw this because collision drawing is enabled, and we have collision
			const bool bShowForCollision = View->Family->EngineShowFlags.Collision && IsCollisionEnabled();

			FPrimitiveViewRelevance Result;
			Result.bDrawRelevance = (IsShown(View) && bProxyVisible) || bShowForCollision;
			Result.bDynamicRelevance = true;
			Result.bShadowRelevance = IsShadowCast(View);
			Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
			return Result;
		}
		virtual uint32 GetMemoryFootprint( void ) const override { return( sizeof( *this ) + GetAllocatedSize() ); }
		uint32 GetAllocatedSize( void ) const { return( FPrimitiveSceneProxy::GetAllocatedSize() ); }

	private:
		const FRotator	Rotation;
		const uint32	bDrawOnlyIfSelected:1;
		const float		CapsuleRadius;
		const float		CapsuleHalfHeight;
		const FColor	ShapeColor;
	};

	return new FDrawCylinderSceneProxy( this );
}


void UCatCapsuleComponent::UpdateBodySetup()
{
	if (PrepareSharedBodySetup<UCapsuleComponent>())
	{
		bUseArchetypeBodySetup = InvalidateOrUpdateCatCapsuleBodySetup<EShapeBodySetupHelper::InvalidateSharingIfStale>(ShapeBodySetup, bUseArchetypeBodySetup, CapsuleRadius, CapsuleHalfHeight, QuatRotation);
	}

	CreateShapeBodySetupIfNeededSphyl();

	if (!bUseArchetypeBodySetup)
	{
		InvalidateOrUpdateCatCapsuleBodySetup<EShapeBodySetupHelper::UpdateBodySetup>(ShapeBodySetup, bUseArchetypeBodySetup, CapsuleRadius, CapsuleHalfHeight, QuatRotation);
	}
}


void UCatCapsuleComponent::CreateShapeBodySetupIfNeededSphyl()
{
	if (ShapeBodySetup == nullptr || ShapeBodySetup->IsPendingKill())
	{
		ShapeBodySetup = NewObject<UBodySetup>(this, NAME_None, RF_Transient);
		if (GUObjectArray.IsDisregardForGC(this))
		{
			ShapeBodySetup->AddToRoot();
		}

		// If this component is in GC cluster, make sure we add the body setup to it to
		ShapeBodySetup->AddToCluster(this);
		// if we got created outside of game thread, but got added to a cluster, 
		// we no longer need the Async flag
		if (ShapeBodySetup->HasAnyInternalFlags(EInternalObjectFlags::Async) && GUObjectClusters.GetObjectCluster(ShapeBodySetup))
		{
			ShapeBodySetup->ClearInternalFlags(EInternalObjectFlags::Async);
		}
		FTransform Custom = FTransform::Identity;
        Custom.SetRotation(QuatRotation());
		FKSphylElem newsphyl;
		newsphyl.SetTransform(Custom);
		ShapeBodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
		ShapeBodySetup->AggGeom.SphylElems.Add(newsphyl);
		ShapeBodySetup->bNeverNeedsCookedCollisionData = true;
		bUseArchetypeBodySetup = false;	//We're making our own body setup, so don't use the archetype's.

		//Update bodyinstance and shapes
		BodyInstance.BodySetup = ShapeBodySetup;
		{
			if(BodyInstance.IsValidBodyInstance())
			{
#if WITH_PHYSX
				FPhysicsCommand::ExecuteWrite(BodyInstance.GetActorReferenceWithWelding(), [this](const FPhysicsActorHandle& Actor)
				{
					TArray<FPhysicsShapeHandle> Shapes;
					BodyInstance.GetAllShapes_AssumesLocked(Shapes);

					for(FPhysicsShapeHandle& Shape : Shapes)	//The reason we iterate is we may have multiple scenes and thus multiple shapes, but they are all pointing to the same geometry
					{
						//Update shape with the new body setup. Make sure to only update shapes owned by this body instance
						if(BodyInstance.IsShapeBoundToBody(Shape))
						{
							SetShapeToNewGeomSphyl(Shape);
						}
					}
				});
#endif
			}
		}
	}
}

#if WITH_PHYSX
void UCatCapsuleComponent::SetShapeToNewGeomSphyl(const FPhysicsShapeHandle& Shape)
{
	FPhysicsInterface::SetUserData(Shape, (void*)ShapeBodySetup->AggGeom.SphylElems[0].GetUserData());
}
#endif // WITH_PHYSX
