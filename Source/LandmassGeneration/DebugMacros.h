#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_POINT(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, false, 1.f);
#define DRAW_POINT_PERM(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, true, -1.f);
#define DRAW_POINT_PERM_STATIC(World, Location, Color) DrawDebugPoint(World, Location, 20.f, Color, true, -1.f);
#define DRAW_LINE(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f);
#define DRAW_LINE_PERM(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f);
#define DRAW_SPHERE(Location, Color) DrawDebugSphere(GetWorld(), Location, 20.f, 12, Color, false, 1.f);
#define DRAW_SPHERE_PERM(Location, Color) DrawDebugSphere(GetWorld(), Location, 20.f, 12, Color, true, -1.f);
#define DRAW_SPHERE_SIZE(Location, Radius, Color) DrawDebugSphere(GetWorld(), Location, Radius, 12, Color, false, 1.f);
#define DRAW_SPHERE_SIZE_PERM(Location, Radius, Color) DrawDebugSphere(GetWorld(), Location, Radius, 12, Color, true, -1.f);
#define PRINT_VECTOR(Vector) UE_LOG(LogTemp, Warning, TEXT("%s"), *Vector.ToString());
#define PRINT_VECTOR_NAME(Name, Vector) UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *Name,*Vector.ToString());
#define PRINT_INT_NAME(Name, Int) UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *Name, Int)