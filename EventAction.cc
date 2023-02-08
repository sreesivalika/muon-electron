//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"
#include "SteppingAction.hh"
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  // fRunAction->AddEdep(fEdep);
  SteppingAction *steppingAction = (SteppingAction *)(G4RunManager::GetRunManager()->GetUserSteppingAction());
  //G4cout<<steppingAction->GetMuEnergy()<<"\t"<<steppingAction->GetEEnergy()<<G4endl;
  if (steppingAction->is_muon_e_event())
  {
    //G4cout<<"mu_e event"<<G4endl;
    G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();
    // G4CsvAnalysisManager *man = G4CsvAnalysisManager::Instance();

    // Get event id from Geant4 step 

    man->FillNtupleDColumn(0,G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
    man->FillNtupleDColumn(1, steppingAction->GetMuPosition().x());
    man->FillNtupleDColumn(2, steppingAction->GetMuPosition().y());
    man->FillNtupleDColumn(3, steppingAction->GetMuPosition().z());

    man->FillNtupleDColumn(4, steppingAction->GetEPosition().x());
    man->FillNtupleDColumn(5, steppingAction->GetEPosition().y());
    man->FillNtupleDColumn(6, steppingAction->GetEPosition().z());
    man->FillNtupleDColumn(7, steppingAction->GetMuEnergy());
    man->FillNtupleDColumn(8, steppingAction->GetEEnergy());//steppingAction->GetEEnergy()
    //G4cout<<steppingAction->GetMuEnergy()<<"\t"<<steppingAction->GetEEnergy()<<G4endl;
    // man->FillNtupleDColumn(0,0);
    // man->FillNtupleDColumn(1, 1);
    // man->FillNtupleDColumn(2, 2);
    // man->FillNtupleDColumn(3, 3);

    // man->FillNtupleDColumn(4, 1);
    // man->FillNtupleDColumn(5, 2);
    // man->FillNtupleDColumn(6, 3);
    man->AddNtupleRow();
    }
  if(G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() % 1000 ==0 )
  G4cout<<G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID()<<" events done ..."<<G4endl;
  steppingAction->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
