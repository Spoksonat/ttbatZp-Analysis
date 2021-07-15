#ifndef analysis_Prueba_Delphes_h
#define analysis_Prueba_Delphes_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"
#include <TH1F.h>
#include <TFile.h>
#include <vector>

namespace MA5
{
class Prueba_Delphes : public AnalyzerBase
{
  INIT_ANALYSIS(Prueba_Delphes,"Prueba_Delphes")

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
  TH1F* plot_Eff_mu;
  TH1F* plot_Eff_e;
  TH1F* plot_Delta_PT_b_alpha_b_beta;

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);
  int nb_jets_geq4 = 0;

 private:
  std::vector<const RecParticleFormat*> leptons;
  std::vector<const RecParticleFormat*> jets;
  std::vector<const RecParticleFormat*> b_jets;
  std::vector<const RecParticleFormat*> j1;
  std::vector<const RecParticleFormat*> j2;
  std::vector<const RecParticleFormat*> b1;
  std::vector<const RecParticleFormat*> b2;
  std::vector<const RecParticleFormat*> electrons;
  std::vector<const RecParticleFormat*> muons;
  std::vector<const RecParticleFormat*> MET;

  bool notMerged;
  bool partiallyMerged;
  bool fullyMerged;
 
  MAuint32 index_b;
  MAuint32 index_bi;
  MAuint32 index_bj;
  Double_t Delta_PT_b_alpha_b_beta;

  MA5::MALorentzVector dijet;
  MA5::MALorentzVector b_dijet;
  MA5::MALorentzVector reconstructed_W;
  MA5::MALorentzVector b_used;
  MA5::MALorentzVector b_not_used;
  MA5::MALorentzVector b_not_used_diff;
  MA5::MALorentzVector b_not_used_indiv;


  MAbool cut_0(std::vector<const RecParticleFormat*> leptons){
    
    bool cut = false;
    for (MAuint32 i=0;i<leptons.size();i++)
    {
      if((leptons[i]->momentum().Pt() > 35.0) &&  (TMath::Abs(leptons[i]->momentum().Eta()) < 2.4) )
      {
        cut = true;
        break;
      }

      else
      {
        cut = false;
      }
    }

    return cut;
  }


  MAbool cut_1(std::vector<const RecParticleFormat*> jets){
    
    bool cut = false;
    int counter = 0;
    for (MAuint32 i=0;i<jets.size();i++)
    {
      if( (jets[i]->momentum().Pt() > 30.0) && (TMath::Abs(jets[i]->momentum().Eta()) < 5.0) )
      {
        counter += 1;
      }
    }

    if(counter >= 2)
    {
      cut = true;
    }

    else
    {
      cut = false;
    }

    return cut;
  }

  MAbool cut_2(std::vector<const RecParticleFormat*> b){
    
    bool cut = false;
    int counter = 0;
    for (MAuint32 i=0;i<b.size();i++)
    {
      if( (b[i]->momentum().Pt() > 30.0) && (TMath::Abs(b[i]->momentum().Eta()) < 2.4) )
      {
        counter += 1;
      }
    }

    if(counter >= 2)
    {
      cut = true;
    }

    else
    {
      cut = false;
    }

    return cut;
  }


  MAbool cut_3(const EventFormat& event){
    
    bool cut = false;
    
    if ( PHYSICS->Transverse->EventMET(event.rec()) > 30 )
    {
      cut = true;
    }

    return cut;
  }

  
  MAbool cut_4(Double_t Delta_PT_b_alpha_b_beta){
    
    bool cut = false;
    
    if ( Delta_PT_b_alpha_b_beta > 60 )
    {
      cut = true;
    }

    return cut;
  }


  void top_reconstruction(std::vector<const RecParticleFormat*> j1, std::vector<const RecParticleFormat*> j2, std::vector<const RecParticleFormat*> b, MA5::MALorentzVector &dijet, MA5::MALorentzVector &b_dijet, MA5::MALorentzVector &reconstructed_W, MA5::MALorentzVector &b_used, MA5::MALorentzVector &b_not_used, MA5::MALorentzVector &b_not_used_diff, MA5::MALorentzVector &b_not_used_indiv){

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

          Delta_PT_b_alpha_b_beta = TMath::Abs(smallest_pt_bibj);

          b_not_used_diff = b[index_bi]->momentum() + b[index_bj]->momentum();
    

     } // end of the else

     } // end of the function top_reconstruction


};
}

#endif
