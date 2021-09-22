#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
#include <fstream>
using namespace std;

void merge_histos()
{
    //vector<std::string> names_files {"bkg1.root", "bkg2.root", "bkg3.root", "bkg4.root", "signal1.root", "signal2.root", "signal3.root", "signal4.root", "signal5.root", "signal6.root", "signal7.root", "signal8.root"};
    vector<std::string> names_files {"ttbarh.root", "ttbarbbar_noh.root", "ttbarttbar.root", "Zprime_bbar_350.root", "Zprime_bbar_1000.root", "Zprime_bbar_3000.root"};

    //vector<std::string> names_files_wo_ext {"$t\\bar{t}h$", "$t\\bar{t}t\\bar{t}$", "$t\\bar{t}b\\bar{b}/h$", "$WWZ$", "$m(Z')=350\\,GeV$", "$m(Z')=500\\,GeV$", "$m(Z')=750\\,GeV$", "$m(Z')=1000\\,GeV$", "$m(Z')=1500\\,GeV$", "$m(Z')=2000\\,GeV$", "$m(Z')=3000\\,GeV$", "$m(Z')=4000\\,GeV$"};
    //vector<std::string> names_files_wo_ext {"$t\\bar{t}h$", "$t\\bar{t}b\\bar{b}/h$", "$t\\bar{t}t\\bar{t}$", };

    //vector<std::string> names {"t#bar{t}h", "t#bar{t}t#bar{t}", "t#bar{t}b#bar{b}/h", "WWZ", "t#bar{t}Z', m(Z')= 350 GeV", "t#bar{t}Z', m(Z')= 500 GeV", "t#bar{t}Z', m(Z')= 750 GeV", "t#bar{t}Z', m(Z')= 1000 GeV", "t#bar{t}Z', m(Z')= 1500 GeV", "t#bar{t}Z', m(Z')= 2000 GeV", "t#bar{t}Z', m(Z')= 3000 GeV", "t#bar{t}Z', m(Z')= 4000 GeV"};
    vector<std::string> names {"t#bar{t}h", "t#bar{t}b#bar{b}/h", "t#bar{t}t#bar{t}", "t#bar{t}Z', m(Z')= 350 GeV", "t#bar{t}Z', m(Z')= 1000 GeV", "t#bar{t}Z', m(Z')= 3000 GeV" };

    vector<std::string> plots {"PT_b1", "PT_b2", "PT_b3", "PT_b4", "PT_j1", "PT_j2", "PT_leptons", "M_b1b2", "M_b1b3", "M_b1b4", "M_b2b3", "M_b2b4", "M_b3b4", "M_j1j2", "MT_b1lMET", "MT_b2lMET", "MT_b3lMET", "MT_b4lMET", "MT_b4lMET", "dETA_b1b2", "dETA_b1b3", "dETA_b1b4", "dETA_b2b3", "dETA_b2b4", "dETA_b3b4", "dPHI_b1b2", "dPHI_b1b3", "dPHI_b1b4", "dPHI_b2b3", "dPHI_b2b4", "dPHI_b3b4", "dPHI_b1l", "dPHI_b2l", "dPHI_b3l", "dPHI_b4l", "dR_b1b2", "dR_b1b3", "dR_b1b4", "dR_b2b3", "dR_b2b4", "dR_b3b4", "dR_j1j2", "dR_b1l", "dR_b2l", "dR_b3l", "dR_b4l", "MET"};

    vector<std::string> plots_names {"p_{T}(b_{1})", "p_{T}(b_{2})", "p_{T}(b_{3})", "p_{T}(b_{4})", "p_{T}(j_{1})", "p_{T}(j_{2})", "p_{T}(leptons)", "M(b_{1}b_{2})", "M(b_{1}b_{3})", "M(b_{1}b_{4})", "M(b_{2}b_{3})", "M(b_{2}b_{4})", "M(b_{3}b_{4})", "M(j_{1}j_{2})", "M_{T}(b_{1}+l+MET)", "M_{T}(b_{2}+l+MET)", "M_{T}(b_{3}+l+MET)", "M_{T}(b_{4}+l+MET)", "M_{T}(l+MET)", "#Delta#eta(b_{1},b_{2})", "#Delta#eta(b_{1},b_{3})", "#Delta#eta(b_{1},b_{4})", "#Delta#eta(b_{2},b_{3})", "#Delta#eta(b_{2},b_{4})", "#Delta#eta(b_{3},b_{4})", "#Delta#phi(b_{1},b_{2})", "#Delta#phi(b_{1},b_{3})", "#Delta#phi(b_{1},b_{4})", "#Delta#phi(b_{2},b_{3})", "#Delta#phi(b_{2},b_{4})", "#Delta#phi(b_{3},b_{4})", "#Delta#phi(b_{1},l)",  "#Delta#phi(b_{2},l)","#Delta#phi(b_{3},l)","#Delta#phi(b_{4},l)", "#DeltaR(b_{1},b_{2})", "#DeltaR(b_{1},b_{3})", "#DeltaR(b_{1},b_{4})", "#DeltaR(b_{2},b_{3})", "#DeltaR(b_{2},b_{4})", "#DeltaR(b_{3},b_{4})", "#DeltaR(j_{1},j_{2})", "#DeltaR(b_{1},l)", "#DeltaR(b_{2},l)", "#DeltaR(b_{3},l)", "#DeltaR(b_{4},l)","MET"};

    vector<std::string> x_labels {"p_{T}(b_{1}) [GeV]", "p_{T}(b_{2}) [GeV]", "p_{T}(b_{3}) [GeV]", "p_{T}(b_{4}) [GeV]", "p_{T}(j_{1}) [GeV]", "p_{T}(j_{2}) [GeV]", "p_{T}(leptons) [GeV]", "M(b_{1}b_{2}) [GeV]", "M(b_{1}b_{3}) [GeV]", "M(b_{1}b_{4}) [GeV]", "M(b_{2}b_{3}) [GeV]", "M(b_{2}b_{4}) [GeV]", "M(b_{3}b_{4}) [GeV]", "M(j_{1}j_{2}) [GeV]", "M_{T}(b_{1}+l+MET) [GeV]", "M_{T}(b_{2}+l+MET) [GeV]", "M_{T}(b_{3}+l+MET) [GeV]", "M_{T}(b_{4}+l+MET) [GeV]", "M_{T}(l+MET) [GeV]", "#Delta#eta(b_{1},b_{2}) [a.u.]", "#Delta#eta(b_{1},b_{3}) [a.u.]", "#Delta#eta(b_{1},b_{4}) [a.u.]", "#Delta#eta(b_{2},b_{3}) [a.u.]", "#Delta#eta(b_{2},b_{4}) [a.u.]", "#Delta#eta(b_{3},b_{4}) [a.u.]", "#Delta#phi(b_{1},b_{2}) [a.u.]", "#Delta#phi(b_{1},b_{3}) [a.u.]", "#Delta#phi(b_{1},b_{4}) [a.u.]", "#Delta#phi(b_{2},b_{3}) [a.u.]", "#Delta#phi(b_{2},b_{4}) [a.u.]", "#Delta#phi(b_{3},b_{4}) [a.u.]", "#Delta#phi(b_{1},l) [a.u.]",  "#Delta#phi(b_{2},l) [a.u.]","#Delta#phi(b_{3},l) [a.u.]","#Delta#phi(b_{4},l) [a.u.]", "#DeltaR(b_{1},b_{2}) [a.u.]", "#DeltaR(b_{1},b_{3}) [a.u.]", "#DeltaR(b_{1},b_{4}) [a.u.]", "#DeltaR(b_{2},b_{3}) [a.u.]", "#DeltaR(b_{2},b_{4}) [a.u.]", "#DeltaR(b_{3},b_{4}) [a.u.]", "#DeltaR(j_{1},j_{2}) [a.u.]", "#DeltaR(b_{1},l) [a.u.]", "#DeltaR(b_{2},l) [a.u.]", "#DeltaR(b_{3},l) [a.u.]", "#DeltaR(b_{4},l) [a.u.]","MET [GeV]"};


    //vector<int> colors {3, 7, 6, 5, 2, 4, 8, 9, 1, 43, 97, 38};
    vector<int> colors {3, 7, 6, 2, 4, 8};

    //vector<int> linestyles {1, 1, 1, 1, 10, 9, 8, 7, 6, 5, 4, 3};
    vector<int> linestyles {1, 1, 1, 10, 9, 8};

    TList *l = new TList();

    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", plots_names[i].c_str());
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        if (plots[i]=="dR_b1b2" || plots[i]=="dR_b1b3" || plots[i]=="dR_b1b4" || plots[i]=="dR_b2b3" || plots[i]=="dR_b2b4" || plots[i]=="dR_b3b4" || plots[i]=="dR_j1j2" || plots[i]=="dR_b1l" || plots[i]=="dR_b2l" || plots[i]=="dR_b3l" || plots[i]=="dR_b4l" ){
            //x_1 = 0.15;
            //x_2 = 0.35;
            x_1 = 0.65;
            x_2 = 0.85;
        }

        else if (plots[i]=="dPHI_b1b2" || plots[i]=="dPHI_b1b3" || plots[i]=="dPHI_b1b4" || plots[i]=="dPHI_b2b3" || plots[i]=="dPHI_b2b4" || plots[i]=="dPHI_b3b4" || plots[i]=="dPHI_b1l" || plots[i]=="dPHI_b2l" || plots[i]=="dPHI_b3l" || plots[i]=="dPHI_b4l"){
            x_1 = 0.67;
            x_2 = 0.87;
        }
        else{
            x_1 = 0.65;
            x_2 = 0.85;
        }

        auto legend = new TLegend(x_1,0.65,x_2,0.85);
    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h = (TH1F*)f.Get(plots[i].c_str());
        h->SetDirectory(0);

        if( (plots[i]=="N_Merged") || (plots[i]=="Eff_mu") || (plots[i]=="Eff_e") )
        {
          h->SetLineColor(colors[j]);
          h->SetLineStyle(linestyles[j]);
          h->SetLineWidth(2);   
        }

        else
        {
          if( (names_files[j] == "Zprime_bbar_350.root") || (names_files[j] == "Zprime_bbar_1000.root") || (names_files[j] == "Zprime_bbar_3000.root") || (names_files[j] == "signal4.root") || (names_files[j] == "signal5.root") || (names_files[j] == "signal6.root") || (names_files[j] == "signal7.root") || (names_files[j] == "signal8.root") )
            {  
              h->SetLineColor(colors[j]);
              h->SetLineStyle(linestyles[j]);
              h->SetLineWidth(2);
            }

            else
            {
              //h->SetFillColor(colors[j]);
              //h->SetFillStyle(1001);
              //h->SetLineColor(0);
              h->SetLineColor(colors[j]);
              h->SetLineStyle(linestyles[j]);
              h->SetLineWidth(3);
            }
        }

        h->Scale(1.0/h->Integral());
    
        if( (plots[i]=="N_Merged") || (plots[i]=="Eff_mu") || (plots[i]=="Eff_e") )
        {
          legend->AddEntry(h,names[j].c_str(),"l");   
        }

        else
        {
          if( (names_files[j] == "Zprime_bbar_350.root") || (names_files[j] == "Zprime_bbar_1000.root") || (names_files[j] == "Zprime_bbar_3000.root") || (names_files[j] == "signal4.root") || (names_files[j] == "signal5.root") || (names_files[j] == "signal6.root") || (names_files[j] == "signal7.root") || (names_files[j] == "signal8.root") )
            {
              legend->AddEntry(h,names[j].c_str(),"l");
            }

            else
            {
              //legend->AddEntry(h,names[j].c_str(),"f");
              legend->AddEntry(h,names[j].c_str(),"l");
            }
        }
     
        legend->SetBorderSize(0);
        hs->Add(h);
         
    }   

        hs->Draw("NOSTACK HIST");
        hs->GetXaxis()->SetTitle(x_labels[i].c_str());
        hs->GetYaxis()->SetTitle("a.u.");
        legend->Draw();
        l->Add(c2);
        std::string filename = "img/" + plots[i] + ".png";
        c2->SaveAs(filename.c_str());
    }

    TFile* Output = new TFile("joined.root", "RECREATE"); 
    l->Write();
    Output->Close();

    
}
