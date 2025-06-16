// Plan en pseudocódigo:
// 1. Identificar el error: el compilador no conoce la definición completa de UBrushComponent.
// 2. Solución: Incluir el encabezado adecuado para UBrushComponent.
// 3. Buscar el encabezado: normalmente es "Components/BrushComponent.h".
// 4. Agregar la directiva #include al inicio del archivo antes de usar GetBrushComponent().

#include "navmesh/MyNavMeshBoundsVolume.h"
#include "Components/BrushComponent.h" // <-- Añadido para definición completa

AMyNavMeshBoundsVolume::AMyNavMeshBoundsVolume()
{
	SetActorScale3D(FVector(50.f, 50.f, 3.f)); // Aumenta el volumen en X e Y

}
