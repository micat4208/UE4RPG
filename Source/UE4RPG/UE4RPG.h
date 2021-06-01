#pragma once

#include "EngineMinimal.h"

#ifndef CUSTOM_LOG_DEFINES
#define CUSTOM_LOG_DEFINES

#define __CLSNAME__ *GetClass()->GetName()

#define LOG(log, ...) UE_LOG(LogTemp, Warning, log, ##__VA_ARGS__)

#endif

