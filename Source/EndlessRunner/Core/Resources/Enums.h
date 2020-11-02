#pragma once

#include "CoreMinimal.h"

#include "Enums.generated.h"

namespace EndlessRunnerEnums {
    UENUM(BlueprintType)
    enum class EMovementDirection : uint8
    {
        UP = 0,
        LEFT,
        DOWN,
        RIGHT 
    };

    UENUM(BlueprintType)
    enum class ETilesType : uint8
    {
        RUNNING = 0,
        WALLRUNNING,
        GLIDING 
    };
}