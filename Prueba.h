#ifndef analysis_Prueba_h
#define analysis_Prueba_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"
#include <TH1F.h>
#include <TFile.h>
#include <vector>

namespace MA5
{
class Prueba : public AnalyzerBase
{
  INIT_ANALYSIS(Prueba,"Prueba")

  TH1F* plot_deltaR_b1b2;
  TH1F* plot_PT_leptons;
  TH1F* plot_ETA_leptons;
  TH1F* plot_PT_b1;
  TH1F* plot_MET;
  TH1F* plot_sdETA_b1b2;
  TH1F* plot_PT_dijet;
  TH1F* plot_N_Merged;
  TH1F* plot_N_notMerged;
  TH1F* plot_N_partiallyMerged;
  TH1F* plot_N_fullyMerged;
  TH1F* plot_PT_dijet_no;
  TH1F* plot_ETA_dijet_no;
  TH1F* plot_M_dijet_no;
  TH1F* plot_PT_dijet_partially;
  TH1F* plot_ETA_dijet_partially;
  TH1F* plot_M_dijet_partially;
  TH1F* plot_PT_b_dijet_partially;
  TH1F* plot_ETA_b_dijet_partially;
  TH1F* plot_M_b_dijet_partially;
  TH1F* plot_PT_b_dijet_fully;
  TH1F* plot_ETA_b_dijet_fully;
  TH1F* plot_M_b_dijet_fully;
  TH1F* plot_PT_b_not_used;
  TH1F* plot_ETA_b_not_used;
  TH1F* plot_PT_b_not_used_diff;
  TH1F* plot_ETA_b_not_used_diff; 
  TH1F* plot_M_b_not_used_diff; 
  TH1F* plot_PT_b_not_used_indiv;
  TH1F* plot_ETA_b_not_used_indiv;
  TH1F* plot_PT_b1b2;
  TH1F* plot_ETA_b1b2; 
  TH1F* plot_M_b1b2; 
  TH1F* plot_sdPHI_lMET;

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
  std::vector<const MCParticleFormat*> lepton_final_state_array;
  std::vector<const MCParticleFormat*> neutrino_final_state_array;
  std::vector<const MCParticleFormat*> j_final_state_array;
  std::vector<const MCParticleFormat*> b_final_state_array;
  std::vector<const MCParticleFormat*> j1_final_state_array;
  std::vector<const MCParticleFormat*> j2_final_state_array;
  std::vector<const MCParticleFormat*> b1_final_state_array;
  std::vector<const MCParticleFormat*> b2_final_state_array;
  std::vector<const MCParticleFormat*> b3_final_state_array;
  std::vector<const MCParticleFormat*> b4_final_state_array;
  bool notMerged;
  bool partiallyMerged;
  bool fullyMerged;
  //int index_b;
  MAuint32 index_b;
  MAuint32 index_bi;
  MAuint32 index_bj;
  MA5::MALorentzVector dijet;
  MA5::MALorentzVector b_dijet;
  MA5::MALorentzVector reconstructed_W;
  MA5::MALorentzVector b_used;
  MA5::MALorentzVector b_not_used;
  MA5::MALorentzVector b_not_used_diff;
  MA5::MALorentzVector b_not_used_indiv;
  MA5::MALorentzVector leptons_lorentz;
  MA5::MALorentzVector invisible_lorentz;

  MAbool is_lepton_final_state(const MCParticleFormat* part){
     if ( part==0 ) return false;
     if ( !PHYSICS->Id->IsFinalState(part) ) return false;
     if ( (part->pdgid()!=-15)&&(part->pdgid()!=-13)&&(part->pdgid()!=-11)&&(part->pdgid()!=11)&&(part->pdgid()!=13)&&(part->pdgid()!=15) ) return false;
     return true; }
  
  MAbool is_neutrino_final_state(const MCParticleFormat* part){
     if ( part==0 ) return false;
     if ( !PHYSICS->Id->IsFinalState(part) ) return false;
     if ( (part->pdgid()!=-16)&&(part->pdgid()!=-14)&&(part->pdgid()!=-12)&&(part->pdgid()!=12)&&(part->pdgid()!=14)&&(part->pdgid()!=16) ) return false;
     return true; }

  MAbool is_j_final_state(const MCParticleFormat* part){
     if ( part==0 ) return false;
     if ( !PHYSICS->Id->IsFinalState(part) ) return false;
     if ( (part->pdgid()!=-4)&&(part->pdgid()!=-3)&&(part->pdgid()!=-2)&&(part->pdgid()!=-1)&&(part->pdgid()!=1)&&(part->pdgid()!=2)&&(part->pdgid()!=3)&&(part->pdgid()!=4)&&(part->pdgid()!=21) ) return false;
     return true; }
  
  MAbool is_b_final_state(const MCParticleFormat* part){
     if ( part==0 ) return false;
     if ( !PHYSICS->Id->IsFinalState(part) ) return false;
     if ( (part->pdgid()!=-5)&&(part->pdgid()!=5) ) return false;
     return true; }

  void top_reconstruction(std::vector<const MCParticleFormat*> j1, std::vector<const MCParticleFormat*> j2, std::vector<const MCParticleFormat*> b, std::vector<const MCParticleFormat*> leptons, std::vector<const MCParticleFormat*> invisible, MA5::MALorentzVector &dijet, MA5::MALorentzVector &b_dijet, MA5::MALorentzVector &reconstructed_W, MA5::MALorentzVector &b_used, MA5::MALorentzVector &b_not_used, MA5::MALorentzVector &b_not_used_diff, MA5::MALorentzVector &b_not_used_indiv, MA5::MALorentzVector &leptons_lorentz, MA5::MALorentzVector &invisible_lorentz){

     dijet = MALorentzVector(); 
     b_dijet = MALorentzVector(); 
     reconstructed_W = MALorentzVector(); 
     b_used = MALorentzVector(); 
     b_not_used = MALorentzVector();  
     b_not_used_diff = MALorentzVector();
     b_not_used_indiv = MALorentzVector();   

     const MALorentzVector j1_p = j1[0]->momentum();
     const MALorentzVector j2_p = j2[0]->momentum();
     dijet = j1_p + j2_p;
     Double_t dr_dijet = j1_p.DeltaR(j2_p);
     //std::cout << "scalar P(j1) + P(j2) : " << j1_p.P() + j2_p.P() << " P(j1j2) : " << dijet.P() << std::endl;
 
     if (dr_dijet > 0.8)
     {
         notMerged = true;
         partiallyMerged = false ;
         fullyMerged = false;
     }
  
     else 
     {
         notMerged = false;
         Double_t smallest_dr_b_dijet = 999999.0;
         for (MAuint32 k=0;k<b.size();k++)
         {
              const MALorentzVector b_p = b[k]->momentum();
              Double_t dr_b_dijet = b_p.DeltaR(dijet);
              if (dr_b_dijet < smallest_dr_b_dijet)
              {
                  smallest_dr_b_dijet = dr_b_dijet;
                  index_b = k;
              }
         }

         if (smallest_dr_b_dijet < 1.0)
         {  
            partiallyMerged = false ;
            fullyMerged = true;
            b_dijet = b[index_b]->momentum() + dijet;
         }

         else
         {
            partiallyMerged = true ;
            fullyMerged = false;
            reconstructed_W = dijet;
            b_dijet = b[index_b]->momentum() + dijet;
         }

          b_used = b[index_b]->momentum();

          for (MAuint32 l=0; l<b.size();l++)
          {
              if(l!=index_b)
              {
                  b_not_used += b[l]->momentum();
              }
          }

          Double_t smallest_pt_bibj = 999999.0;

          for (MAuint32 l1=0; l1<b.size();l1++)
          {	
            for (MAuint32 l2=0; l2<l1;l2++)
          
            {
              if(l1!=index_b && l2!=index_b && l1!=l2)
              {
                  Double_t diff = b[l1]->momentum().Pt() - b[l2]->momentum().Pt();
                  if(TMath::Abs(diff) < smallest_pt_bibj)
                  {
                      smallest_pt_bibj = diff;
                      index_bi = l1;
                      index_bj = l2;
                  }
              }
            }
          }

          b_not_used_diff = b[index_bi]->momentum() + b[index_bj]->momentum();

          for (MAuint32 n=0; n<leptons.size();n++)
          {
              leptons_lorentz += leptons[n]->momentum();
          }
  
          for (MAuint32 m=0; m<invisible.size();m++)
          {
              invisible_lorentz += invisible[m]->momentum();
          }        
   

    

     } // end of the else

     } // end of the function top_reconstruction



};
}

#endif
