/// \file enctranceCounter.cc
/// \brief Main program of the Entrance Counter simulation

#include <G4RunManagerFactory.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

// #include "Randomize.hh"

int main(int argc, char** argv) {
    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Optionally: choose a different Random engine...
    // G4Random::setTheEngine(new CLHEP::MTwistEngine);
    // TODO: Save this seed to a file
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);
    G4cout << "Random generator seed is: " << G4Random::getTheSeed();

    // Construct the default run manager
    //
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // Set Physics List
    runManager->SetUserInitialization(new PhysicsList());

    // Construction
    runManager->SetUserInitialization(new DetectorConstruction());

    // Action initialization
    runManager->SetUserInitialization(new ActionInitialization());

    // Initialize visualization with the default graphics system
    auto visManager = new G4VisExecutive(argc, argv);
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    if (!ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete visManager;
    delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
