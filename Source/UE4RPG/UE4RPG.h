#pragma once

#include "EngineMinimal.h"

#ifndef FN_PTR_DEFINE
#define FN_PTR_DEFINE
#define Func(fnPtrName, Params, ...) auto fnPtrName = [##__VA_ARGS__]Params
#endif



#ifndef CUSTOM_LOG_DEFINES
#define CUSTOM_LOG_DEFINES

#define __CLSNAME__ *ThisClass::StaticClass()->GetName()

#define LOG(log, ...) UE_LOG(LogTemp, Warning, log, ##__VA_ARGS__)

#endif

