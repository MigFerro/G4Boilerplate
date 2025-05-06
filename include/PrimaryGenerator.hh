#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include <G4VUserPrimaryGeneratorAction.hh>

class G4Event;
class G4ParticleGun;

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
   public:
    PrimaryGenerator();
    ~PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

   private:
    G4ParticleGun *fParticleGun;
};

#endif
