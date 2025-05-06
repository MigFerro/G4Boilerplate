#include "DetectorConstruction.hh"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4VPhysicalVolume.hh>

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    G4double worldX = 1. * m;
    G4double worldY = 1. * m;
    G4double worldZ = 1. * m;

    G4Box *solidWorld = new G4Box("World", worldX / 2, worldY / 2, worldZ / 2);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "World", 0, false, 0, checkOverlaps);

    return physWorld;
}
