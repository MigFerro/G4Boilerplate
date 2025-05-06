#include "PrimaryGenerator.hh"

#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>

PrimaryGenerator::PrimaryGenerator() {
    G4int particlesPerEvent = 1;

    fParticleGun = new G4ParticleGun(particlesPerEvent);

    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., 1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);

    fParticleGun->SetParticleMomentum(12. * MeV);

    G4ParticleTable *pTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = pTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(particle);
}

PrimaryGenerator::~PrimaryGenerator() { delete fParticleGun; }

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent) { fParticleGun->GeneratePrimaryVertex(anEvent); }
