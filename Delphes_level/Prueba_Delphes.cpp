#include "SampleAnalyzer/User/Analyzer/Prueba_Delphes.h"
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
bool Prueba_Delphes::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  // initialize variables, histos
  
  // Initializing PhysicsService for RECO
  PHYSICS->recConfig().Reset();

  // Histos

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

  Manager()->AddHisto("PT_dijet", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_dijet = new TH1F("PT_dijet", "PT_dijet", 100, 0.0, 1000.0);

  Manager()->AddHisto("N_Merged", 3, 0.0,4.0); /*Name, bins, x_initial, x_final*/
  plot_N_Merged = new TH1F("N_Merged", "N_Merged", 3, 0.0,4.0);

  Manager()->AddHisto("N_notMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_notMerged = new TH1F("N_notMerged", "N_notMerged", 100, 0.0,2.0);

  Manager()->AddHisto("N_partiallyMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_partiallyMerged = new TH1F("N_partiallyMerged", "N_partiallyMerged", 100, 0.0,2.0);

  Manager()->AddHisto("N_fullyMerged", 100, 0.0,2.0); /*Name, bins, x_initial, x_final*/
  plot_N_fullyMerged = new TH1F("N_fullyMerged", "N_fullyMerged", 100, 0.0,2.0);

  Manager()->AddHisto("PT_dijet_no", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_dijet_no = new TH1F("PT_dijet_no", "PT_dijet_no", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_dijet_no", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_dijet_no = new TH1F("ETA_dijet_no", "ETA_dijet_no", 100, -8.0,8.0);

  Manager()->AddHisto("M_dijet_no", 100, 0.0,100.0); /*Name, bins, x_initial, x_final*/
  plot_M_dijet_no = new TH1F("M_dijet_no", "M_dijet_no", 100, -0.0,100.0);

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

  Manager()->AddHisto("PT_b_not_used_diff", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b_not_used_diff = new TH1F("PT_b_not_used_diff", "PT_b_not_used_diff", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b_not_used_diff", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b_not_used_diff = new TH1F("ETA_b_not_used_diff", "ETA_b_not_used_diff", 100, -8.0,8.0);

  Manager()->AddHisto("M_b_not_used_diff", 100, 0.0,4500.0); /*Name, bins, x_initial, x_final*/
  plot_M_b_not_used_diff = new TH1F("M_b_not_used_diff", "M_b_not_used_diff", 100, 0.0,4500.0);

  Manager()->AddHisto("PT_b_not_used_indiv", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b_not_used_indiv = new TH1F("PT_b_not_used_indiv", "PT_b_not_used_indiv", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b_not_used_indiv", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b_not_used_indiv = new TH1F("ETA_b_not_used_indiv", "ETA_b_not_used_indiv", 100, -8.0,8.0);

  Manager()->AddHisto("PT_b1b2", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_PT_b1b2 = new TH1F("PT_b1b2", "PT_b1b2", 100, 0.0, 1000.0);

  Manager()->AddHisto("ETA_b1b2", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_ETA_b1b2 = new TH1F("ETA_b1b2", "ETA_b1b2", 100, -8.0,8.0);

  Manager()->AddHisto("M_b1b2", 100, 0.0,4500.0); /*Name, bins, x_initial, x_final*/
  plot_M_b1b2 = new TH1F("M_b1b2", "M_b1b2", 100, 0.0,4500.0);

  Manager()->AddHisto("sdPHI_lMET", 100, -8.0,8.0); /*Name, bins, x_initial, x_final*/
  plot_sdPHI_lMET = new TH1F("sdPHI_lMET", "sdPHI_lMET", 100, -8.0,8.0);

  Manager()->AddHisto("Eff_mu", 6, 0.5, 6.5); /*Name, bins, x_initial, x_final*/
  plot_Eff_mu = new TH1F("Eff_mu", "Eff_mu", 6, 0.5, 6.5);

  Manager()->AddHisto("Eff_e", 6, 0.5, 6.5); /*Name, bins, x_initial, x_final*/
  plot_Eff_e = new TH1F("Eff_e", "Eff_e", 6, 0.5, 6.5);

  Manager()->AddHisto("Delta_PT_b_alpha_b_beta", 100, 0.0,1000.0); /*Name, bins, x_initial, x_final*/
  plot_Delta_PT_b_alpha_b_beta = new TH1F("Delta_PT_b_alpha_b_beta", "Delta_PT_b_alpha_b_beta", 100, 0.0, 1000.0);

  cout << "END   Initialization" << endl;
  
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void Prueba_Delphes::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  cout << "Numero de eventos con 4 b: " << nb_jets_geq4 << endl;

  // saving histograms
  //auto c1 = new TCanvas("c1","Histogram example",200,10,700,500);
  TFile* Output = new TFile("output.root", "RECREATE");
  plot_deltaR_b1b2->SetLineStyle(1);
  plot_PT_leptons->SetLineStyle(1);
  plot_ETA_leptons->SetLineStyle(1);
  plot_PT_b1->SetLineStyle(1);
  plot_MET->SetLineStyle(1);
  plot_sdETA_b1b2->SetLineStyle(1);
  plot_PT_dijet->SetLineStyle(1);
  plot_N_Merged->SetLineStyle(1);
  plot_N_notMerged->SetLineStyle(1);
  plot_N_partiallyMerged->SetLineStyle(1);
  plot_N_fullyMerged->SetLineStyle(1);
  plot_PT_dijet_no->SetLineStyle(1);
  plot_ETA_dijet_no->SetLineStyle(1);
  plot_M_dijet_no->SetLineStyle(1);
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
  plot_PT_b_not_used_diff->SetLineStyle(1);
  plot_ETA_b_not_used_diff->SetLineStyle(1);
  plot_M_b_not_used_diff->SetLineStyle(1);
  plot_PT_b_not_used_indiv->SetLineStyle(1);
  plot_ETA_b_not_used_indiv->SetLineStyle(1);
  plot_PT_b1b2->SetLineStyle(1);
  plot_ETA_b1b2->SetLineStyle(1);
  plot_M_b1b2->SetLineStyle(1);
  plot_sdPHI_lMET->SetLineStyle(1);
  plot_Eff_mu->SetLineStyle(1);
  plot_Eff_e->SetLineStyle(1);
  plot_Delta_PT_b_alpha_b_beta->SetLineStyle(1);

  plot_deltaR_b1b2->Draw("HIST");
  plot_PT_leptons->Draw("HIST");
  plot_ETA_leptons->Draw("HIST");
  plot_PT_b1->Draw("HIST");
  plot_MET->Draw("HIST");
  plot_sdETA_b1b2->Draw("HIST");
  plot_PT_dijet->Draw("HIST");

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
  plot_PT_dijet_no->Draw("HIST");
  plot_ETA_dijet_no->Draw("HIST");
  plot_M_dijet_no->Draw("HIST");
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
  plot_PT_b_not_used_diff->Draw("HIST");
  plot_ETA_b_not_used_diff->Draw("HIST");
  plot_M_b_not_used_diff->Draw("HIST");
  plot_PT_b_not_used_indiv->Draw("HIST");
  plot_ETA_b_not_used_indiv->Draw("HIST");
  plot_PT_b1b2->Draw("HIST");
  plot_ETA_b1b2->Draw("HIST");
  plot_M_b1b2->Draw("HIST");
  plot_sdPHI_lMET->Draw("HIST");
  
  TAxis* b = plot_Eff_mu->GetXaxis();
  b->SetBit(TAxis::kLabelsHori); 
  b->SetBinLabel(1,"No Cuts");
  b->SetBinLabel(2,"Cut I"); 
  b->SetBinLabel(3,"Cut II"); 
  b->SetBinLabel(4,"Cut III");
  b->SetBinLabel(5,"Cut IV");
  b->SetBinLabel(6,"Cut V");
  plot_Eff_mu->Draw("HIST");

  TAxis* c = plot_Eff_e->GetXaxis();
  c->SetBit(TAxis::kLabelsHori); 
  c->SetBinLabel(1,"No Cuts");
  c->SetBinLabel(2,"Cut I"); 
  c->SetBinLabel(3,"Cut II"); 
  c->SetBinLabel(4,"Cut III");
  c->SetBinLabel(5,"Cut IV");
  c->SetBinLabel(6,"Cut V");
  plot_Eff_e->Draw("HIST");

  plot_Delta_PT_b_alpha_b_beta->Draw("HIST");

  
  plot_deltaR_b1b2->Write();
  plot_PT_leptons->Write();
  plot_ETA_leptons->Write();
  plot_PT_b1->Write();
  plot_MET->Write();
  plot_sdETA_b1b2->Write();
  plot_PT_dijet->Write();
  plot_N_Merged->Write();
  plot_N_notMerged->Write();
  plot_N_partiallyMerged->Write();
  plot_N_fullyMerged->Write();
  plot_PT_dijet_no->Write();
  plot_ETA_dijet_no->Write();
  plot_M_dijet_no->Write();
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
  plot_PT_b_not_used_diff->Write();
  plot_ETA_b_not_used_diff->Write();
  plot_M_b_not_used_diff->Write();
  plot_PT_b_not_used_indiv->Write();
  plot_ETA_b_not_used_indiv->Write();
  plot_PT_b1b2->Write();
  plot_ETA_b1b2->Write();
  plot_M_b1b2->Write();
  plot_sdPHI_lMET->Write();
  plot_Eff_mu->Write();
  plot_Eff_e->Write();
  plot_Delta_PT_b_alpha_b_beta->Write();

  Output->Close();

  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool Prueba_Delphes::Execute(SampleFormat& sample, const EventFormat& event)
{
  // Event weight
  double myWeight=1.;
  if (!Configuration().IsNoEventWeight() && event.mc()!=0) myWeight=event.mc()->weight();

  Manager()->InitializeForNewEvent(myWeight);
  if (event.rec()!=0)
  {
    int nb_jets = 0;

    for (MAuint32 i=0;i<event.rec()->jets().size();i++)
    {
      const RecJetFormat& jet = event.rec()->jets()[i];
      
      if (jet.btag() == 1)
      {
         nb_jets = nb_jets + 1;
      }
    }

    if(nb_jets >= 4)
    {
      nb_jets_geq4 += 1;
    }


    leptons.clear();
    jets.clear();
    j1.clear();
    j2.clear();
    b_jets.clear();
    electrons.clear();
    muons.clear();
    MET.clear();

    for (MAuint32 i=0;i<event.rec()->jets().size();i++)
    {
      if (event.rec()->jets()[i].btag() != 1) jets.push_back(&(event.rec()->jets()[i]));
    }

    for (MAuint32 i=0;i<event.rec()->jets().size();i++)
    {
      if (event.rec()->jets()[i].btag() == 1) b_jets.push_back(&(event.rec()->jets()[i]));
    }

    for (MAuint32 i=0;i<event.rec()->electrons().size();i++)
    {
      leptons.push_back(&(event.rec()->electrons()[i]));
      electrons.push_back(&(event.rec()->electrons()[i]));
    }
    
    for (MAuint32 i=0;i<event.rec()->muons().size();i++)
    {
      leptons.push_back(&(event.rec()->muons()[i]));
      muons.push_back(&(event.rec()->muons()[i])); 
    }
    
    for (MAuint32 i=0;i<event.rec()->taus().size();i++)
    {
      leptons.push_back(&(event.rec()->taus()[i]));
    }

    MET.push_back(&(event.rec()->MET()));


    j1 = SORTER->rankFilter(jets,1,PTordering);

    j2 = SORTER->rankFilter(jets,2,PTordering);

    b1 = SORTER->rankFilter(b_jets,1,PTordering);

    b2 = SORTER->rankFilter(b_jets,2,PTordering);

    if(b_jets.size() >= 3 && j1.size() != 0 && j2.size() != 0 && leptons.size() != 0)
    {
    //************************************************** Top reconstruction function ***************************************************
     top_reconstruction(j1, j2, b_jets, dijet, b_dijet, reconstructed_W, b_used, b_not_used, b_not_used_diff, b_not_used_indiv);
    //*********************************************************** Histograms *************************************************************

    //if (leptons.size() == 0){ // esto si pasa!
    //cout << "WFT" << endl; 
    //}


    bool isElectron = false;
    bool isMuon = false;

   
    if ( event.rec()->muons().size() >=1 ) 
    {
      isMuon = true;
    }

    if ( event.rec()->electrons().size() >=1 ) 
    {
      isElectron = true;
    }

   if(isMuon)
   {
      if(notMerged)
      {
          Manager()->FillHisto("Eff_mu", 1);
          plot_Eff_mu->Fill(1);

          if(cut_0(muons))
          {
            Manager()->FillHisto("Eff_mu", 2);
            plot_Eff_mu->Fill(2);
          }

          if( (cut_0(muons)) && (cut_1(jets)) )
          {
            Manager()->FillHisto("Eff_mu", 3);
            plot_Eff_mu->Fill(3);
          }

          if( (cut_0(muons)) && (cut_1(jets)) && (cut_2(b_jets)) )
          {
            Manager()->FillHisto("Eff_mu", 4);
            plot_Eff_mu->Fill(4);
          }

          if( (cut_0(muons)) && (cut_1(jets)) && (cut_2(b_jets)) && (cut_3(event))  )
          {
            Manager()->FillHisto("Eff_mu",5);
            plot_Eff_mu->Fill(5);
         
            Manager()->FillHisto("Delta_PT_b_alpha_b_beta", Delta_PT_b_alpha_b_beta);
            plot_Delta_PT_b_alpha_b_beta->Fill(Delta_PT_b_alpha_b_beta);

          }

          if( (cut_0(muons)) && (cut_1(jets)) && (cut_2(b_jets)) && (cut_3(event)) && (cut_4(Delta_PT_b_alpha_b_beta))   )
          {
            Manager()->FillHisto("Eff_mu",6);
            plot_Eff_mu->Fill(6);
          }
 
      }

   } // end if(isMuon) 

   if(isElectron)
   {
      if(notMerged)
      {
          Manager()->FillHisto("Eff_e", 1);
          plot_Eff_e->Fill(1);

          if(cut_0(electrons))
          {
            Manager()->FillHisto("Eff_e", 2);
            plot_Eff_e->Fill(2);
          }

          if( (cut_0(electrons)) && (cut_1(jets)) )
          {
            Manager()->FillHisto("Eff_e", 3);
            plot_Eff_e->Fill(3);
          }


          if( (cut_0(electrons)) && (cut_1(jets)) && (cut_2(b_jets)))
          {
            Manager()->FillHisto("Eff_e",4);
            plot_Eff_e->Fill(4);
          }

          if( (cut_0(electrons)) && (cut_1(jets)) && (cut_2(b_jets)) && (cut_3(event)) )
          {
            Manager()->FillHisto("Eff_e",5);
            plot_Eff_e->Fill(5);
          }

          if( (cut_0(electrons)) && (cut_1(jets)) && (cut_2(b_jets)) && (cut_3(event)) && (cut_4(Delta_PT_b_alpha_b_beta))   )
          {
            Manager()->FillHisto("Eff_e",6);
            plot_Eff_e->Fill(6);
          }
 
      }

   } // end if(isElectron)


    //MET

    Manager()->FillHisto("MET", PHYSICS->Transverse->EventMET(event.rec()));
    plot_MET->Fill(PHYSICS->Transverse->EventMET(event.rec()));

    // delta R ( bottom_1 , bottom_2 ) histogram 
   
    for (MAuint32 i=0;i< b1.size();i++)
    {
    for (MAuint32 j=0;j< b2.size();j++)
    {
     if ( b1[i] == b2[j] ) continue;
      Manager()->FillHisto("deltaR_b1b2", b1[i]->dr(b2[j]));
      plot_deltaR_b1b2->Fill(b1[i]->dr(b2[j]));
    }
    }
 

    //PT (leptons)

    for (MAuint32 i=0; i < leptons.size(); i++)
    {
      Manager()->FillHisto("PT_leptons", leptons[i]->pt());
      plot_PT_leptons->Fill(leptons[i]->pt());
    }
    
    // Lepton ETA Histogram


    for (MAuint32 j=0;j<leptons.size();j++)
    {
      Manager()->FillHisto("ETA_leptons", leptons[j]->eta());
      plot_ETA_leptons->Fill(leptons[j]->eta());
    } 

    // Bottom 1 pt Histogram
   
    for (MAuint32 j=0;j<b1.size();j++)
    {
      Manager()->FillHisto("PT_b1", b1[j]->pt());
      plot_PT_b1->Fill(b1[j]->pt());
    }

    // Delta Eta (bottom_1, bottom_2) Histogram
  
    vector<set<const RecParticleFormat*> > combinations; // We create a vector with all the combinations that we can do with bottom_1 and bottom_2

    MAuint32 index[2];
    for (index[0]=0;index[0]<b1.size();index[0]++) // We go through bottom_1 and bottom_2 in order to join them
    {
    for (index[1]=0;index[1]<b2.size();index[1]++)
    {
        if (b2[index[1]]==b1[index[0]]) continue; // We exclude the cases when the two bottom quarks are the same

       
        set<const RecParticleFormat*> combination; // We create a particular combination of bottom_1 and bottom_2
        for (MAuint32 i=0;i<2;i++)
        {
          combination.insert(b1[index[i]]); // Joining bottom_1 and bottom_2
          combination.insert(b2[index[i]]);
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
        sdeta+=b1[index[0]]->eta();
        sdeta-=b2[index[1]]->eta();
        Manager()->FillHisto("sdETA_b1b2", sdeta);
        plot_sdETA_b1b2->Fill(sdeta);
    }
    }

    // dijet j1j2 pt Histogram
   
    
     Manager()->FillHisto("PT_dijet", dijet.Pt());
     plot_PT_dijet->Fill(dijet.Pt());

    // pt b1b2

     Manager()->FillHisto("PT_b1b2", (b1[0]->momentum() + b2[0]->momentum()).Pt());
     plot_PT_b1b2->Fill((b1[0]->momentum() + b2[0]->momentum()).Pt());

    // ETA b1b2

     Manager()->FillHisto("ETA_b1b2", (b1[0]->momentum() + b2[0]->momentum()).Eta());
     plot_ETA_b1b2->Fill((b1[0]->momentum() + b2[0]->momentum()).Eta());


  // M b1b2

     Manager()->FillHisto("M_b1b2", (b1[0]->momentum() + b2[0]->momentum()).M());
     plot_M_b1b2->Fill((b1[0]->momentum() + b2[0]->momentum()).M());

   
      if(notMerged)
      {
         // Fill number of not Merged events histogram
         Manager()->FillHisto("N_notMerged", notMerged);
         plot_N_notMerged->Fill(notMerged);

         Manager()->FillHisto("N_Merged", 1);
         plot_N_Merged->Fill(1);

         Manager()->FillHisto("PT_dijet_no", dijet.Pt());
         plot_PT_dijet_no->Fill(dijet.Pt());

         Manager()->FillHisto("ETA_dijet_no", dijet.Eta());
         plot_ETA_dijet_no->Fill(dijet.Eta());

         Manager()->FillHisto("M_dijet_no", dijet.M());
         plot_M_dijet_no->Fill(dijet.M());

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
         // PT b-quark not used in the top reconstruction as only one TLorentzVector
   
         Manager()->FillHisto("PT_b_not_used", b_not_used.Pt());
         plot_PT_b_not_used->Fill(b_not_used.Pt());

         // ETA b-quark not used in the top reconstruction as only one TLorentzVector
   
         Manager()->FillHisto("ETA_b_not_used", b_not_used.Eta());
         plot_ETA_b_not_used->Fill(b_not_used.Eta());

         // PT of b_ib_j, where b_i,b_j != b_used and PT(b_i) - PT(b_j) is minumum.  

         Manager()->FillHisto("PT_b_not_used_diff", b_not_used_diff.Pt());
         plot_PT_b_not_used_diff->Fill(b_not_used_diff.Pt());

         // ETA of b_ib_j, where b_i,b_j != b_used and PT(b_i) - PT(b_j) is minumum.
   
         Manager()->FillHisto("ETA_b_not_used_diff", b_not_used_diff.Eta());
         plot_ETA_b_not_used_diff->Fill(b_not_used_diff.Eta());

         // M of b_ib_j, where b_i,b_j != b_used and PT(b_i) - PT(b_j) is minumum.
   
         Manager()->FillHisto("M_b_not_used_diff", b_not_used_diff.M());
         plot_M_b_not_used_diff->Fill(b_not_used_diff.M());

         // Delta pt of b_alpha and b_beta       
 
         //Manager()->FillHisto("Delta_PT_b_alpha_b_beta", Delta_PT_b_alpha_b_beta);
         //plot_Delta_PT_b_alpha_b_beta->Fill(Delta_PT_b_alpha_b_beta);

         // PT b-quark not used in the top reconstruction as individual entities
   

         for (MAuint32 l=0; l<b_jets.size();l++)
          {
              if(l!=index_b)
              {
                  Manager()->FillHisto("PT_b_not_used_indiv", b_jets[l]->momentum().Pt());
                  plot_PT_b_not_used_indiv->Fill(b_jets[l]->momentum().Pt());
              }
          }

         

         // ETA b-quark not used in the top reconstruction as individual entities
   
         for (MAuint32 l=0; l<b_jets.size();l++)
          {
              if(l!=index_b)
              {
                  Manager()->FillHisto("ETA_b_not_used_indiv", b_jets[l]->momentum().Eta());
                  plot_ETA_b_not_used_indiv->Fill(b_jets[l]->momentum().Eta());
              }
          }
      }


   // Delta phi (lepton, MET) Histogram

    vector<set<const RecParticleFormat*> > combinations_lMET; // We create a vector with all the combinations that we can do with lepton, MET=neutrinos

    MAuint32 index_lMET[2];
    for (index_lMET[0]=0;index_lMET[0]<leptons.size();index_lMET[0]++) // We go through lepton, MET in order to join them
    {
    for (index_lMET[1]=0;index_lMET[1]<MET.size();index_lMET[1]++)
    {
        if (MET[index_lMET[1]]==leptons[index_lMET[0]]) continue; // We exclude the cases when the two are the same

       
        set<const RecParticleFormat*> combination_lMET; // We create a particular combination of lepton, MET
        for (MAuint32 i=0;i<2;i++)
        {
          combination_lMET.insert(leptons[index_lMET[i]]); // Joining lepton, MET=neutrinos
          combination_lMET.insert(MET[index_lMET[i]]);
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
        sdphi+=leptons[index_lMET[0]]->phi();
        sdphi-=MET[index_lMET[1]]->phi();
        Manager()->FillHisto("sdPHI_lMET", sdphi);
        plot_sdPHI_lMET->Fill(sdphi);
    }
    }
    
   } // End if b_jets >= x, j1 != 0 and j2 != 0

  } 
  return true;
}

//
  //{
    //cout << "---------------NEW EVENT-------------------" << endl;
    /*
    // Looking through the reconstructed electron collection
    for (MAuint32 i=0;i<event.rec()->electrons().size();i++)
    {
      const RecLeptonFormat& elec = event.rec()->electrons()[i];
      cout << "----------------------------------" << endl;
      cout << "Electron" << endl;
      cout << "----------------------------------" << endl;
      cout << "index=" << i+1 
                << " charge=" << elec.charge() << endl;
      cout << "px=" << elec.px()
                << " py=" << elec.py()
                << " pz=" << elec.pz()
                << " e="  << elec.e()
                << " m="  << elec.m() << endl;
      cout << "pt=" << elec.pt() 
                << " eta=" << elec.eta() 
                << " phi=" << elec.phi() << endl;
      cout << "pointer address to the matching MC particle: " 
                << elec.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed mls
uon collection
    for (MAuint32 i=0;i<event.rec()->muons().size();i++)
    {
      const RecLeptonFormat& mu = event.rec()->muons()[i];
      cout << "----------------------------------" << endl;
      cout << "Muon" << endl;
      cout << "----------------------------------" << endl;
      cout << "index=" << i+1 
                << " charge=" << mu.charge() << endl;
      cout << "px=" << mu.px()
                << " py=" << mu.py()
                << " pz=" << mu.pz()
                << " e="  << mu.e()
                << " m="  << mu.m() << endl;
      cout << "pt=" << mu.pt() 
                << " eta=" << mu.eta() 
                << " phi=" << mu.phi() << endl;
      cout << "ET/PT isolation criterion =" << mu.ET_PT_isol() << endl;
      cout << "pointer address to the matching MC particle: " 
           << mu.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed hadronic tau collection
    for (MAuint32 i=0;i<event.rec()->taus().size();i++)
    {
      const RecTauFormat& tau = event.rec()->taus()[i];
      cout << "----------------------------------" << endl;
      cout << "Tau" << endl;
      cout << "----------------------------------" << endl;
      cout << "tau: index=" << i+1 
                << " charge=" << tau.charge() << endl;
      cout << "px=" << tau.px()
                << " py=" << tau.py()
                << " pz=" << tau.pz()
                << " e="  << tau.e()
                << " m="  << tau.m() << endl;
      cout << "pt=" << tau.pt() 
                << " eta=" << tau.eta() 
                << " phi=" << tau.phi() << endl;
      cout << "pointer address to the matching MC particle: " 
           << tau.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed jet collection
    for (MAuint32 i=0;i<event.rec()->jets().size();i++)
    {
      const RecJetFormat& jet = event.rec()->jets()[i];
      cout << "----------------------------------" << endl;
      cout << "Jet" << endl;
      cout << "----------------------------------" << endl;
      cout << "jet: index=" << i+1 
           << " charge=" << jet.charge() << endl;
      cout << "px=" << jet.px()
           << " py=" << jet.py()
           << " pz=" << jet.pz()
           << " e="  << jet.e()
           << " m="  << jet.m() << endl;
      cout << "pt=" << jet.pt() 
           << " eta=" << jet.eta() 
           << " phi=" << jet.phi() << endl;
      cout << "b-tag=" << jet.btag()
           << " true b-tag (before eventual efficiency)=" 
           << jet.true_btag() << endl;
      cout << "EE/HE=" << jet.EEoverHE()
           << " ntracks=" << jet.ntracks() << endl;
      cout << endl;
    }

    // Transverse missing energy (MET)
    cout << "MET pt=" << event.rec()->MET().pt()
         << " phi=" << event.rec()->MET().phi() << endl;
    cout << endl;

    // Transverse missing hadronic energy (MHT)
    cout << "MHT pt=" << event.rec()->MHT().pt()
              << " phi=" << event.rec()->MHT().phi() << endl;
    cout << endl;

    // Total transverse energy (TET)
    cout << "TET=" << event.rec()->TET() << endl;
    cout << endl;

    // Total transverse hadronic energy (THT)
    cout << "THT=" << event.rec()->THT() << endl;
    cout << endl;*/


