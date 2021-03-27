#include "SampleAnalyzer/User/Analyzer/Prueba.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"
#include <TFile.h>
#include <TCanvas.h>
#include <vector>
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------

bool Prueba::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  // initialize variables, histos

  PHYSICS->mcConfig().Reset();

  // definition of the multiparticle "hadronic" 
  PHYSICS->mcConfig().AddHadronicId(1); // down
  PHYSICS->mcConfig().AddHadronicId(2); // up
  PHYSICS->mcConfig().AddHadronicId(3); // strange
  PHYSICS->mcConfig().AddHadronicId(4); // charm
  PHYSICS->mcConfig().AddHadronicId(5); // bottom
  PHYSICS->mcConfig().AddHadronicId(6); // top
  PHYSICS->mcConfig().AddHadronicId(-1);
  PHYSICS->mcConfig().AddHadronicId(-2);
  PHYSICS->mcConfig().AddHadronicId(-3);
  PHYSICS->mcConfig().AddHadronicId(-4); 
  PHYSICS->mcConfig().AddHadronicId(-5);
  PHYSICS->mcConfig().AddHadronicId(21); // gluon(s)

  // definition of the multiparticle "invisible"
  PHYSICS->mcConfig().AddInvisibleId(12); // neutrino_e
  PHYSICS->mcConfig().AddInvisibleId(14); // neutrino_mu
  PHYSICS->mcConfig().AddInvisibleId(16); //neutrino_tau
  PHYSICS->mcConfig().AddInvisibleId(-12);
  PHYSICS->mcConfig().AddInvisibleId(-14);
  PHYSICS->mcConfig().AddInvisibleId(-16);

  Manager()->AddRegionSelection("myregion");

  // Definition of histograms

  Manager()->AddHisto("deltaR_b1b2", 100, 0.0,6.3); /*Name, bins, x_initial, x_final*/ //dR(b,jj)
  plot_deltaR_b1b2 = new TH1F("deltaR_b1b2", "deltaR_b1b2", 100, 0.0, 6.3);

  Manager()->AddHisto("PT_leptons", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_leptons = new TH1F("PT_leptons", "PT_leptons", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_leptons", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_leptons = new TH1F("ETA_leptons", "ETA_leptons", 100, -8.0, 8.0);

  Manager()->AddHisto("PT_b1", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b1 = new TH1F("PT_b1", "PT_b1", 100, 0.0, 1000.0);

  Manager()->AddHisto("MET", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_MET = new TH1F("MET", "MET", 100, 0.0, 1000.0);

  Manager()->AddHisto("sdETA_b1b2", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_sdETA_b1b2 = new TH1F("sdETA_b1b2", "sdETA_b1b2", 100, -8.0,8.0);

  Manager()->AddHisto("N_Merged", 3, 0.0,4.0); /*Name, bins, x_initial, x_final*/
  plot_N_Merged = new TH1F("N_Merged", "N_Merged", 3, 0.0,4.0);

  Manager()->AddHisto("N_notMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_notMerged = new TH1F("N_notMerged", "N_notMerged", 100, 0.0,2.0);

  Manager()->AddHisto("N_partiallyMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_partiallyMerged = new TH1F("N_partiallyMerged", "N_partiallyMerged", 100, 0.0,2.0);

  Manager()->AddHisto("N_fullyMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_fullyMerged = new TH1F("N_fullyMerged", "N_fullyMerged", 100, 0.0,2.0);

  Manager()->AddHisto("PT_dijet_partially", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_dijet_partially = new TH1F("PT_dijet_partially", "PT_dijet_partially", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_dijet_partially", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_dijet_partially = new TH1F("ETA_dijet_partially", "ETA_dijet_partially", 100, -8.0,8.0);

  Manager()->AddHisto("M_dijet_partially", 100, 0.0,100.0); /*Name, bins, x_initial, x_final*/
  plot_M_dijet_partially = new TH1F("M_dijet_partially", "M_dijet_partially", 100, -0.0,100.0);

  Manager()->AddHisto("PT_b_dijet_partially", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b_dijet_partially = new TH1F("PT_b_dijet_partially", "PT_dijet_partially", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b_dijet_partially", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b_dijet_partially = new TH1F("ETA_b_dijet_partially", "ETA_b_dijet_partially", 100, -8.0,8.0);

  Manager()->AddHisto("M_b_dijet_partially", 100, 100.0,200.0); /*Name, bins, x_initial, x_final*/
  plot_M_b_dijet_partially = new TH1F("M_b_dijet_partially", "M_b_dijet_partially", 100, 100.0,200.0);

  Manager()->AddHisto("PT_b_dijet_fully", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b_dijet_fully = new TH1F("PT_b_dijet_fully", "PT_b_dijet_fully", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b_dijet_fully", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b_dijet_fully = new TH1F("ETA_b_dijet_fully", "ETA_b_dijet_fully", 100, -8.0,8.0);

  Manager()->AddHisto("M_b_dijet_fully", 100, 100.0,200.0); /*Name, bins, x_initial, x_final*/
  plot_M_b_dijet_fully = new TH1F("M_b_dijet_fully", "M_b_dijet_fully", 100, 100.0,200.0);

  Manager()->AddHisto("PT_b_not_used", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b_not_used = new TH1F("PT_b_not_used", "PT_b_not_used", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b_not_used", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b_not_used = new TH1F("ETA_b_not_used", "ETA_b_not_used", 100, -8.0,8.0);

  Manager()->AddHisto("sdPHI_lMET", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_sdPHI_lMET = new TH1F("sdPHI_lMET", "sdPHI_lMET", 100, -8.0,8.0);

  

  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void Prueba::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histograms
  //auto c1 = new TCanvas("c1","Histogram example",200,10,700,500);
  TFile* Output = new TFile("output.root", "RECREATE");
  plot_deltaR_b1b2->SetLineStyle(1);
  plot_PT_leptons->SetLineStyle(1);
  plot_ETA_leptons->SetLineStyle(1);
  plot_PT_b1->SetLineStyle(1);
  plot_MET->SetLineStyle(1);
  plot_sdETA_b1b2->SetLineStyle(1);
  plot_N_Merged->SetLineStyle(1);
  plot_N_notMerged->SetLineStyle(1);
  plot_N_partiallyMerged->SetLineStyle(1);
  plot_N_fullyMerged->SetLineStyle(1);
  plot_PT_dijet_partially->SetLineStyle(1);
  plot_ETA_dijet_partially->SetLineStyle(1);
  plot_M_dijet_partially->SetLineStyle(1);
  plot_PT_b_dijet_partially->SetLineStyle(1);
  plot_ETA_b_dijet_partially->SetLineStyle(1);
  plot_M_b_dijet_partially->SetLineStyle(1);
  plot_PT_b_dijet_fully->SetLineStyle(1);
  plot_ETA_b_dijet_fully->SetLineStyle(1);
  plot_M_b_dijet_fully->SetLineStyle(1);
  plot_PT_b_not_used->SetLineStyle(1);
  plot_ETA_b_not_used->SetLineStyle(1);
  plot_sdPHI_lMET->SetLineStyle(1);


  plot_deltaR_b1b2->Draw("HIST");
  plot_PT_leptons->Draw("HIST");
  plot_ETA_leptons->Draw("HIST");
  plot_PT_b1->Draw("HIST");
  plot_MET->Draw("HIST");
  plot_sdETA_b1b2->Draw("HIST");
  
  //TCanvas *c2 = new TCanvas();
  //if (plot_PT_leptons->GetSumw2N() == 0) plot_PT_leptons->Sumw2(kTRUE);
  //plot_N_Merged->Scale(1.0/plot_N_Merged->Integral());
  TAxis* a = plot_N_Merged->GetXaxis();
  a->SetBit(TAxis::kLabelsHori); 
  a->SetBinLabel(1,"Not Merged"); 
  a->SetBinLabel(2,"Partially Merged"); 
  a->SetBinLabel(3,"Fully Merged");
  plot_N_Merged->Draw("HIST");
  //c2->SaveAs("N_merged.png");
  
  plot_N_notMerged->Draw("HIST");
  plot_N_partiallyMerged->Draw("HIST");
  plot_N_fullyMerged->Draw("HIST");
  plot_PT_dijet_partially->Draw("HIST");
  plot_ETA_dijet_partially->Draw("HIST");
  plot_M_dijet_partially->Draw("HIST");
  plot_PT_b_dijet_partially->Draw("HIST");
  plot_ETA_b_dijet_partially->Draw("HIST");
  plot_M_b_dijet_partially->Draw("HIST");
  plot_PT_b_dijet_fully->Draw("HIST");
  plot_ETA_b_dijet_fully->Draw("HIST");
  plot_M_b_dijet_fully->Draw("HIST");
  plot_PT_b_not_used->Draw("HIST");
  plot_ETA_b_not_used->Draw("HIST");
  plot_sdPHI_lMET->Draw("HIST");

  
  plot_deltaR_b1b2->Write();
  plot_PT_leptons->Write();
  plot_ETA_leptons->Write();
  plot_PT_b1->Write();
  plot_MET->Write();
  plot_sdETA_b1b2->Write();
  plot_N_Merged->Write();
  plot_N_notMerged->Write();
  plot_N_partiallyMerged->Write();
  plot_N_fullyMerged->Write();
  plot_PT_dijet_partially->Write();
  plot_ETA_dijet_partially->Write();
  plot_M_dijet_partially->Write();
  plot_PT_b_dijet_partially->Write();
  plot_ETA_b_dijet_partially->Write();
  plot_M_b_dijet_partially->Write();
  plot_PT_b_dijet_fully->Write();
  plot_ETA_b_dijet_fully->Write();
  plot_M_b_dijet_fully->Write();
  plot_PT_b_not_used->Write();
  plot_ETA_b_not_used->Write();
  plot_sdPHI_lMET->Write();
  Output->Close();
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool Prueba::Execute(SampleFormat& sample, const EventFormat& event)
{

  MAfloat32 __event_weight__ = 1.0;
  if (weighted_events_ && event.mc()!=0) __event_weight__ = event.mc()->weight();

  if (sample.mc()!=0) sample.mc()->addWeightedEvents(__event_weight__);
  Manager()->InitializeForNewEvent(__event_weight__);   

  
      lepton_final_state_array.clear(); //clear the vectors that contain leptons, neutrinos, j and b in each iteration over all the events
      neutrino_final_state_array.clear();
      j_final_state_array.clear(); // These jets are non-bquark jets
      b_final_state_array.clear();
      j1_final_state_array.clear(); // These jets are non-bquark jets
      j2_final_state_array.clear(); // These jets are non-bquark jets
      b1_final_state_array.clear();
      b2_final_state_array.clear();
      b3_final_state_array.clear();
      b4_final_state_array.clear();
  
  // ************************************** Defining lepton, neutrino, jets and b-quarks arrays ******************************************
  
    for (MAuint32 i=0;i<event.mc()->particles().size();i++) // Fill the vectors that contain leptons,neutrinos, ...
    {
      if (is_lepton_final_state((&(event.mc()->particles()[i])))) 
      {
        lepton_final_state_array.push_back(&(event.mc()->particles()[i]));
      }

      if (is_neutrino_final_state((&(event.mc()->particles()[i])))) 
      {
        neutrino_final_state_array.push_back(&(event.mc()->particles()[i]));
      }

      if (is_j_final_state((&(event.mc()->particles()[i])))) 
      {
          j_final_state_array.push_back(&(event.mc()->particles()[i]));
      }

      if (is_b_final_state((&(event.mc()->particles()[i])))) 
      {     
         b_final_state_array.push_back(&(event.mc()->particles()[i]));
      }
    }
  
  // Defining j[1], j[2], b[1], b[2], b[3], b[4]
  
  j1_final_state_array=SORTER->rankFilter(j_final_state_array,1,PTordering);

  j2_final_state_array=SORTER->rankFilter(j_final_state_array,2,PTordering);

  b1_final_state_array=SORTER->rankFilter(b_final_state_array,1,PTordering);

  b2_final_state_array=SORTER->rankFilter(b_final_state_array,2,PTordering);

  b3_final_state_array=SORTER->rankFilter(b_final_state_array,3,PTordering);

  b4_final_state_array=SORTER->rankFilter(b_final_state_array,4,PTordering);


  //************************************************** Top reconstruction function ***************************************************
  

   top_reconstruction(j1_final_state_array, j2_final_state_array, b_final_state_array, lepton_final_state_array, neutrino_final_state_array, dijet, b_dijet, reconstructed_W, b_used, b_not_used, leptons_lorentz, invisible_lorentz);


  //*********************************************************** Histograms *************************************************************

   // delta R ( bottom_1 , bottom_2 ) histogram 

    for (MAuint32 i=0;i< b1_final_state_array.size();i++)
    {
    for (MAuint32 j=0;j< b2_final_state_array.size();j++)
    {
     if ( b1_final_state_array[i] == b2_final_state_array[j] ) continue;
      Manager()->FillHisto("deltaR_b1b2", b1_final_state_array[i]->dr(b2_final_state_array[j]));
      plot_deltaR_b1b2->Fill(b1_final_state_array[i]->dr(b2_final_state_array[j]));
    }
    }


  // Lepton pt Histogram


    for (MAuint32 j=0;j<lepton_final_state_array.size();j++)
    {
      Manager()->FillHisto("PT_leptons", lepton_final_state_array[j]->pt());
      plot_PT_leptons->Fill(lepton_final_state_array[j]->pt());
    }

 


  // Lepton ETA Histogram


    for (MAuint32 j=0;j<lepton_final_state_array.size();j++)
    {
      Manager()->FillHisto("ETA_leptons", lepton_final_state_array[j]->eta());
      plot_ETA_leptons->Fill(lepton_final_state_array[j]->eta());
    } 

 

  // Bottom 1 pt Histogram
   
    for (MAuint32 j=0;j<b1_final_state_array.size();j++)
    {
      Manager()->FillHisto("PT_b1", b1_final_state_array[j]->pt());
      plot_PT_b1->Fill(b1_final_state_array[j]->pt());
    }

  // Delta Eta (bottom_1, bottom_2) Histogram

    vector<set<const MCParticleFormat*> > combinations; // We create a vector with all the combinations that we can do with bottom_1 and bottom_2

    MAuint32 index[2];
    for (index[0]=0;index[0]<b1_final_state_array.size();index[0]++) // We go through bottom_1 and bottom_2 in order to join them
    {
    for (index[1]=0;index[1]<b2_final_state_array.size();index[1]++)
    {
        if (b2_final_state_array[index[1]]==b1_final_state_array[index[0]]) continue; // We exclude the cases when the two bottom quarks are the same

       
        set<const MCParticleFormat*> combination; // We create a particular combination of bottom_1 and bottom_2
        for (MAuint32 i=0;i<2;i++)
        {
          combination.insert(b1_final_state_array[index[i]]); // Joining bottom_1 and bottom_2
          combination.insert(b2_final_state_array[index[i]]);
        }

        MAbool matched=false;

        for (MAuint32 i=0;i<combinations.size();i++)
        {
          if (combinations[i]==combination) // Checking if the particular combination is already inside of the vector of all combinations
          {    
            matched=true; 
            break;
          } 
        }

        if (matched) continue; // If the particular combination is already inside of the vector of all the combinations, then we continue
        else combinations.push_back(combination); // Else, we add this particular combination in the vector

        MAdouble64 sdeta=0; // We declare the variable that will contain the value of sdETA
        sdeta+=b1_final_state_array[index[0]]->eta();
        sdeta-=b2_final_state_array[index[1]]->eta();
        Manager()->FillHisto("sdETA_b1b2", sdeta);
        plot_sdETA_b1b2->Fill(sdeta);
    }
    }

    // MET 
   
     Manager()->FillHisto("MET", PHYSICS->Transverse->EventMET(event.mc()));
     plot_MET->Fill(PHYSICS->Transverse->EventMET(event.mc()));
 

    // Number of total events divide in notMerged, partiallyMerged and fullyMerged


      if(notMerged)
      {
         // Fill number of not Merged events histogram
         Manager()->FillHisto("N_notMerged", notMerged);
         plot_N_notMerged->Fill(notMerged);

         Manager()->FillHisto("N_Merged", 1);
         plot_N_Merged->Fill(1);
      }

      if(partiallyMerged)
      {
         // Fill number of partially Merged events histogram
         Manager()->FillHisto("N_partiallyMerged", partiallyMerged);
         plot_N_partiallyMerged->Fill(partiallyMerged);

         Manager()->FillHisto("PT_dijet_partially", reconstructed_W.Pt());
         plot_PT_dijet_partially->Fill(reconstructed_W.Pt());

         Manager()->FillHisto("ETA_dijet_partially", reconstructed_W.Eta());
         plot_ETA_dijet_partially->Fill(reconstructed_W.Eta());

         Manager()->FillHisto("M_dijet_partially", reconstructed_W.M());
         plot_M_dijet_partially->Fill(reconstructed_W.M());

         Manager()->FillHisto("PT_b_dijet_partially", b_dijet.Pt());
         plot_PT_b_dijet_partially->Fill(b_dijet.Pt());

         Manager()->FillHisto("ETA_b_dijet_partially", b_dijet.Eta());
         plot_ETA_b_dijet_partially->Fill(b_dijet.Eta());

         Manager()->FillHisto("M_b_dijet_partially", b_dijet.M());
         plot_M_b_dijet_partially->Fill(b_dijet.M());

         Manager()->FillHisto("N_Merged", 2);
         plot_N_Merged->Fill(2);
      }


      if(fullyMerged)
      {
         // Fill number of fully Merged events histogram
         Manager()->FillHisto("N_fullyMerged", fullyMerged);
         plot_N_fullyMerged->Fill(fullyMerged);

         Manager()->FillHisto("PT_b_dijet_fully", b_dijet.Pt());
         plot_PT_b_dijet_fully->Fill(b_dijet.Pt());

         Manager()->FillHisto("ETA_b_dijet_fully", b_dijet.Eta());
         plot_ETA_b_dijet_fully->Fill(b_dijet.Eta());

         Manager()->FillHisto("M_b_dijet_fully", b_dijet.M());
         plot_M_b_dijet_fully->Fill(b_dijet.M());

         Manager()->FillHisto("N_Merged", 3);
         plot_N_Merged->Fill(3);
      }

      if(!notMerged)
      {
         // PT b-quark not used in the top reconstruction
   
         Manager()->FillHisto("PT_b_not_used", b_not_used.Pt());
         plot_PT_b_not_used->Fill(b_not_used.Pt());

         // ETA b-quark not used in the top reconstruction
   
         Manager()->FillHisto("ETA_b_not_used", b_not_used.Eta());
         plot_ETA_b_not_used->Fill(b_not_used.Eta());
      }



     // Delta phi (lepton, MET=neutrinos) Histogram

    vector<set<const MCParticleFormat*> > combinations_lMET; // We create a vector with all the combinations that we can do with lepton, MET=neutrinos

    MAuint32 index_lMET[2];
    for (index_lMET[0]=0;index_lMET[0]<lepton_final_state_array.size();index_lMET[0]++) // We go through lepton, MET=neutrinos in order to join them
    {
    for (index_lMET[1]=0;index_lMET[1]<neutrino_final_state_array.size();index_lMET[1]++)
    {
        if (neutrino_final_state_array[index_lMET[1]]==lepton_final_state_array[index_lMET[0]]) continue; // We exclude the cases when the two are the same

       
        set<const MCParticleFormat*> combination_lMET; // We create a particular combination of lepton, MET=neutrinos
        for (MAuint32 i=0;i<2;i++)
        {
          combination_lMET.insert(lepton_final_state_array[index_lMET[i]]); // Joining lepton, MET=neutrinos
          combination_lMET.insert(neutrino_final_state_array[index_lMET[i]]);
        }

        MAbool matched_lMET=false;

        for (MAuint32 i=0;i<combinations_lMET.size();i++)
        {
          if (combinations_lMET[i]==combination_lMET) // Checking if the particular combination is already inside of the vector of all combinations
          {    
            matched_lMET=true; 
            break;
          } 
        }

        if (matched_lMET) continue; // If the particular combination is already inside of the vector of all the combinations, then we continue
        else combinations_lMET.push_back(combination_lMET); // Else, we add this particular combination in the vector

        MAdouble64 sdphi=0; // We declare the variable that will contain the value of sdPHI
        sdphi+=lepton_final_state_array[index_lMET[0]]->phi();
        sdphi-=neutrino_final_state_array[index_lMET[1]]->phi();
        Manager()->FillHisto("sdPHI_lMET", sdphi);
        plot_sdPHI_lMET->Fill(sdphi);
    }
    }
   

  return true;
}

