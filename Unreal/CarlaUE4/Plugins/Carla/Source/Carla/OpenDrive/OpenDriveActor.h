// Copyright (c) 2019 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "GameFramework/Actor.h"

#include "Traffic/RoutePlanner.h"
#include "Vehicle/VehicleSpawnPoint.h"

#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"


#include "OpenDriveActor.generated.h"

UCLASS()
class CARLA_API AOpenDriveActor : public AActor
{
  GENERATED_BODY()

protected:

  /// ���ڴ��ͼ�꾫���UBillboardComponent
  UBillboardComponent *SpriteComponent;

  /// ѩ�����ڹ�������
  UTexture2D *SpriteTexture;

private:

  UPROPERTY()
  TArray<AVehicleSpawnPoint *> VehicleSpawners;

#if WITH_EDITORONLY_DATA
  /// ʹ��OpenDrive�ļ�������Ϊcurrent.umap�����ɵ�·����
  UPROPERTY(Category = "Generate", EditAnywhere)
  bool bGenerateRoutes = false;
#endif // WITH_EDITORONLY_DATA

  /// ������ʻ��·��֮��ľ���
  UPROPERTY(Category = "Generate", EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
  float RoadAccuracy = 2.f;

  /// �������
  UPROPERTY(Category = "Generate", EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
  float TriggersHeight = 100.f;

#if WITH_EDITORONLY_DATA
  /// ɾ��֮ǰ���ɵĵ�·���硣���⣬���б�Ҫ��������ɾ��������
  UPROPERTY(Category = "Generate", EditAnywhere)
  bool bRemoveRoutes = false;
#endif // WITH_EDITORONLY_DATA

  /// ���Ϊ�棬����·��ʱ�����ò�����
  UPROPERTY(Category = "Spawners", EditAnywhere)
  bool bAddSpawners = false;

  /// ��������ʵ��������Ҳ����������·��
  UPROPERTY(Category = "Spawners", EditAnywhere)
  bool bOnIntersections = false;

  /// ȷ�������������ÿ��RoutePlanner�ķ��ø߶�
  UPROPERTY(Category = "Spawners", EditAnywhere)
  float SpawnersHeight = 300.f;

#if WITH_EDITORONLY_DATA
  /// ��Ҫʱɾ���ѷ��õĲ�����
  UPROPERTY(Category = "Spawners", EditAnywhere)
  bool bRemoveCurrentSpawners = false;
#endif // WITH_EDITORONLY_DATA

#if WITH_EDITORONLY_DATA
  /// ��ʾ/��������������Ϣ
  UPROPERTY(Category = "Debug", EditAnywhere)
  bool bShowDebug = true;
#endif // WITH_EDITORONLY_DATA

public:

  AOpenDriveActor(const FObjectInitializer &ObjectInitializer);

  void BuildRoutes();

  void BuildRoutes(FString MapName);

  /// ɾ��������ǰ���ɵ���������ARoutePlanner��VehicleSpawner���Ա����ص�
  void RemoveRoutes();

  void DebugRoutes() const;

  void RemoveDebugRoutes() const;

#if WITH_EDITOR
  void PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent);

#endif // WITH_EDITOR

  void AddSpawners();

  void RemoveSpawners();

  UPROPERTY()
  TArray<ARoutePlanner *> RoutePlanners;
};
