import ROOT
from ROOT import TLorentzVector, TH1F
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from bcml4pheno import bcml_model
from bcml4pheno import get_elijah_ttbarzp_cs
from bcml4pheno import get_settings
import scipy.interpolate
import matplotlib.pyplot as plt
from datetime import datetime
from bcml4pheno import cross_section_helper


def top_reconstruction(j1, j2, b):
    global dijet
    global b_dijet
    global reconstructed_W
    global b_used
    global b_not_used
    global b_not_used_diff
    global b_not_used_indiv
    global notMerged
    global partiallyMerged
    global fullyMerged
    global index_b
    global index_bi
    global index_bj
    global Delta_PT_b_alpha_b_beta

    dijet = j1 + j2
    dr_dijet = j1.DeltaR(j2)

    if (dr_dijet > 0.8):

         notMerged = True
         partiallyMerged = False
         fullyMerged = False


    else:

         notMerged = False
         smallest_dr_b_dijet = 999999.0
         for k in range(len(b)):

              dr_b_dijet = b[k].DeltaR(dijet)
              if (dr_b_dijet < smallest_dr_b_dijet):

                  smallest_dr_b_dijet = dr_b_dijet
                  index_b = k


         if (smallest_dr_b_dijet < 1.0):

            partiallyMerged = False
            fullyMerged = True
            b_dijet = b[index_b] + dijet


         else:

            partiallyMerged = True
            fullyMerged = False
            reconstructed_W = dijet
            b_dijet = b[index_b] + dijet


         b_used = b[index_b]
         b_not_used = TLorentzVector()

         for l in range(len(b)):

              if(l!=index_b):

                  b_not_used += b[l]


         smallest_pt_bibj = 999999.0

         for l1 in range(len(b)):

            for l2 in range(l1):

              if(l1!=index_b and l2!=index_b and l1!=l2):

                  diff = b[l1].Pt() - b[l2].Pt()
                  if(abs(diff) < smallest_pt_bibj):

                      smallest_pt_bibj = diff
                      index_bi = l1
                      index_bj = l2

         Delta_PT_b_alpha_b_beta = abs(smallest_pt_bibj)

         b_not_used_diff = b[index_bi] + b[index_bj]



def PT(TLV):
    return TLV.Pt()

entries = ["ttbarh", "ttbarttbar" ,"ttbarbbar_noh", "Zprime_bbar_350", "Zprime_bbar_1000", "Zprime_bbar_3000"]
type_entries = ["bkg", "bkg", "bkg", "signal", "signal", "signal" ]
jobs = [99, 99, 99, 19, 19, 19]
#jobs = [1, 1, 1, 1, 1, 1]

c1 = ROOT.TCanvas("c1", "Titulo")
plot_deltaR_b1b2 = TH1F("deltaR_b1b2", "deltaR_b1b2", 100, 0.0, 6.3)
plot_PT_leptons = TH1F("PT_leptons", "PT_leptons", 100, 0.0, 1000.0)
plot_ETA_leptons = TH1F("ETA_leptons", "ETA_leptons", 100, -8.0, 8.0)
plot_PT_b1 = TH1F("PT_b1", "PT_b1", 100, 0.0, 1000.0)
plot_MET = TH1F("MET", "MET", 100, 0.0, 1000.0)
plot_sdETA_b1b2 = TH1F("sdETA_b1b2", "sdETA_b1b2", 100, -8.0,8.0)
plot_PT_dijet = TH1F("PT_dijet", "PT_dijet", 100, 0.0, 1000.0)
plot_N_Merged = TH1F("N_Merged", "N_Merged", 3, 0.0,4.0)
plot_N_notMerged = TH1F("N_notMerged", "N_notMerged", 100, 0.0,2.0)
plot_N_partiallyMerged = TH1F("N_partiallyMerged", "N_partiallyMerged", 100, 0.0,2.0)
plot_N_fullyMerged = TH1F("N_fullyMerged", "N_fullyMerged", 100, 0.0,2.0)
plot_PT_dijet_no = TH1F("PT_dijet_no", "PT_dijet_no", 100, 0.0, 1000.0)
plot_ETA_dijet_no = TH1F("ETA_dijet_no", "ETA_dijet_no", 100, -8.0,8.0)
plot_M_dijet_no = TH1F("M_dijet_no", "M_dijet_no", 100, -0.0,100.0)
plot_PT_dijet_partially = TH1F("PT_dijet_partially", "PT_dijet_partially", 100, 0.0, 1000.0)
plot_ETA_dijet_partially = TH1F("ETA_dijet_partially", "ETA_dijet_partially", 100, -8.0,8.0)
plot_M_dijet_partially = TH1F("M_dijet_partially", "M_dijet_partially", 100, -0.0,100.0)
plot_PT_b_dijet_partially = TH1F("PT_b_dijet_partially", "PT_dijet_partially", 100, 0.0, 1000.0)
plot_ETA_b_dijet_partially = TH1F("ETA_b_dijet_partially", "ETA_b_dijet_partially", 100, -8.0,8.0)
plot_M_b_dijet_partially = TH1F("M_b_dijet_partially", "M_b_dijet_partially", 100, 100.0,200.0)
plot_PT_b_dijet_fully = TH1F("PT_b_dijet_fully", "PT_b_dijet_fully", 100, 0.0, 1000.0)
plot_ETA_b_dijet_fully = TH1F("ETA_b_dijet_fully", "ETA_b_dijet_fully", 100, -8.0,8.0)
plot_M_b_dijet_fully = TH1F("M_b_dijet_fully", "M_b_dijet_fully", 100, 100.0,200.0)
plot_PT_b_not_used = TH1F("PT_b_not_used", "PT_b_not_used", 100, 0.0, 1000.0)
plot_ETA_b_not_used = TH1F("ETA_b_not_used", "ETA_b_not_used", 100, -8.0,8.0)
plot_PT_b_not_used_diff = TH1F("PT_b_not_used_diff", "PT_b_not_used_diff", 100, 0.0, 1000.0)
plot_ETA_b_not_used_diff = TH1F("ETA_b_not_used_diff", "ETA_b_not_used_diff", 100, -8.0,8.0)
plot_M_b_not_used_diff = TH1F("M_b_not_used_diff", "M_b_not_used_diff", 100, 0.0,4500.0)
plot_PT_b_not_used_indiv = TH1F("PT_b_not_used_indiv", "PT_b_not_used_indiv", 100, 0.0, 1000.0)
plot_ETA_b_not_used_indiv = TH1F("ETA_b_not_used_indiv", "ETA_b_not_used_indiv", 100, -8.0,8.0)
plot_PT_b1b2 = TH1F("PT_b1b2", "PT_b1b2", 100, 0.0, 1000.0)
plot_ETA_b1b2 = TH1F("ETA_b1b2", "ETA_b1b2", 100, -8.0,8.0)
plot_M_b1b2 = TH1F("M_b1b2", "M_b1b2", 100, 0.0,4500.0)
plot_sdPHI_lMET = TH1F("sdPHI_lMET", "sdPHI_lMET", 100, -8.0,8.0)
plot_Eff_mu = TH1F("Eff_mu", "Eff_mu", 6, 0.5, 6.5)
plot_Eff_e = TH1F("Eff_e", "Eff_e", 6, 0.5, 6.5)
plot_Delta_PT_b_alpha_b_beta = TH1F("Delta_PT_b_alpha_b_beta", "Delta_PT_b_alpha_b_beta", 100, 0.0, 1000.0)

arrs = []

print("Begin of Data Reading")

for n_signal, signal in enumerate(entries):

  arr1 = []
  f = ROOT.TFile(signal + ".root", "recreate")

  for ind in range(1,jobs[n_signal]+1):
    directory= str("../from_disco3/with_delphes/" + signal + "/" + signal + "_" + str(ind) + "/Events/run_01/tag_1_delphes_events.root")
    File = ROOT.TChain("Delphes;1")
    File.Add(directory)
    Number = File.GetEntries()

    print("Input: " + signal + "_" + str(ind))

    for i in range(Number):
    	#print("Evento: " + str(i))
        Entry = File.GetEntry(i)

        jets = []
        bjets = []
        electrons = []
        muons = []
        leptons = []
        METs = []

        EntryFromBranch_j = File.Jet.GetEntries()
        for j in range(EntryFromBranch_j):

                BTag = File.GetLeaf("Jet.BTag").GetValue(j)
		        #print("PT = {}, BTag = {}".format(PT,BTag) )
                if (BTag != 1):
                  jet = TLorentzVector()
                  jet_PT, jet_Eta, jet_Phi, jet_M  = File.GetLeaf("Jet.PT").GetValue(j), File.GetLeaf("Jet.Eta").GetValue(j), File.GetLeaf("Jet.Phi").GetValue(j), File.GetLeaf("Jet.Mass").GetValue(j)
                  jet.SetPtEtaPhiM(jet_PT, jet_Eta, jet_Phi, jet_M)
                  jets.append(jet)

                elif (BTag == 1):
                  bjet = TLorentzVector()
                  bjet_PT, bjet_Eta, bjet_Phi, bjet_M  = File.GetLeaf("Jet.PT").GetValue(j), File.GetLeaf("Jet.Eta").GetValue(j), File.GetLeaf("Jet.Phi").GetValue(j), File.GetLeaf("Jet.Mass").GetValue(j)
                  bjet.SetPtEtaPhiM(bjet_PT, bjet_Eta, bjet_Phi, bjet_M)
                  bjets.append(bjet)

        EntryFromBranch_e = File.Electron.GetEntries()
        for j in range(EntryFromBranch_e):
          electron = TLorentzVector()
          electron_PT, electron_Eta, electron_Phi, electron_M  = File.GetLeaf("Electron.PT").GetValue(j), File.GetLeaf("Electron.Eta").GetValue(j), File.GetLeaf("Electron.Phi").GetValue(j), 0.000510998928
          electron.SetPtEtaPhiM(electron_PT, electron_Eta, electron_Phi, electron_M)
          electrons.append(electron)

        EntryFromBranch_mu = File.Muon.GetEntries()
        for j in range(EntryFromBranch_mu):
          muon = TLorentzVector()
          muon_PT, muon_Eta, muon_Phi, muon_M  = File.GetLeaf("Muon.PT").GetValue(j), File.GetLeaf("Muon.Eta").GetValue(j), File.GetLeaf("Muon.Phi").GetValue(j), 0.1056583745
          muon.SetPtEtaPhiM(muon_PT, muon_Eta, muon_Phi, muon_M)
          muons.append(muon)

        EntryFromBranch_MET = File.MissingET.GetEntries()
        for j in range(EntryFromBranch_MET):
          MET = TLorentzVector()
          MET_PT, MET_Eta, MET_Phi, MET_M  = File.GetLeaf("MissingET.MET").GetValue(j), File.GetLeaf("MissingET.Eta").GetValue(j), File.GetLeaf("MissingET.Phi").GetValue(j), 0.0
          MET.SetPtEtaPhiM(MET_PT, MET_Eta, MET_Phi, MET_M)
          METs.append(MET)


        leptons = electrons + muons


        if (len(bjets) == 4 and len(jets) >= 2 and len(leptons) != 0):

            jets.sort(reverse = True, key=PT)
            bjets.sort(reverse = True, key=PT)
            j1, j2 = jets[0], jets[1]
            b1, b2 = bjets[0], bjets[1]
            top_reconstruction(j1, j2, bjets)

            
            plot_PT_b1.Fill(b1.Pt())

            for lepton in leptons:
                plot_PT_leptons.Fill(lepton.Pt())

            MET
            for MET in METs:
                plot_MET.Fill(MET.Pt())

           

            if(notMerged):
                plot_N_Merged.Fill(1)

            if(partiallyMerged):
                plot_N_Merged.Fill(2)

            if(fullyMerged):
                plot_N_Merged.Fill(3)
            
        
            

            leptons_tot = np.sum(np.array(leptons))
            MET = np.sum(np.array(METs))

            
            row = np.array([bjets[0].Pt(), bjets[1].Pt(), bjets[2].Pt(), bjets[3].Pt(), jets[0].Pt(), jets[1].Pt(), np.sum(np.array(leptons)).Pt(), (bjets[0] + bjets[1]).M(), (bjets[0] + bjets[2]).M(), (bjets[0] + bjets[3]).M(), (bjets[1] + bjets[2]).M(), (bjets[1] + bjets[3]).M(), (bjets[2] + bjets[3]).M(), (jets[0] + jets[1]).M(), (bjets[0] + leptons_tot + MET).Mt(), (bjets[1] + leptons_tot + MET).Mt(), (bjets[2] + leptons_tot + MET).Mt(), (bjets[3] + leptons_tot + MET).Mt(), (leptons_tot + MET).Mt(), (bjets[0].Eta() - bjets[1].Eta()), (bjets[0].Eta() - bjets[2].Eta()), (bjets[0].Eta() - bjets[3].Eta()), (bjets[1].Eta() - bjets[2].Eta()), (bjets[1].Eta() - bjets[3].Eta()), (bjets[2].Eta() - bjets[3].Eta()), bjets[0].DeltaPhi(bjets[1]), bjets[0].DeltaPhi(bjets[2]), bjets[0].DeltaPhi(bjets[3]), bjets[1].DeltaPhi(bjets[2]), bjets[1].DeltaPhi(bjets[3]), bjets[2].DeltaPhi(bjets[3]), bjets[0].DeltaPhi(leptons_tot), bjets[1].DeltaPhi(leptons_tot), bjets[2].DeltaPhi(leptons_tot), bjets[3].DeltaPhi(leptons_tot), bjets[0].DeltaR(bjets[1]), bjets[0].DeltaR(bjets[2]), bjets[0].DeltaR(bjets[3]), bjets[1].DeltaR(bjets[2]), bjets[1].DeltaR(bjets[3]), bjets[2].DeltaR(bjets[3]), jets[0].DeltaR(jets[1]), bjets[0].DeltaR(leptons_tot), bjets[1].DeltaR(leptons_tot), bjets[2].DeltaR(leptons_tot), bjets[3].DeltaR(leptons_tot), MET.Pt()])
            arr1.append(row)
            
            
  arrs.append(arr1)          
  
  plot_deltaR_b1b2.Draw("HIST")
  plot_PT_leptons.Draw("HIST")
  plot_ETA_leptons.Draw("HIST")
  plot_PT_b1.Draw("HIST")
  plot_MET.Draw("HIST")
  plot_sdETA_b1b2.Draw("HIST")
  plot_PT_dijet.Draw("HIST")

  a = plot_N_Merged.GetXaxis()
  a.SetBinLabel(1,"Not Merged")
  a.SetBinLabel(2,"Partially Merged")
  a.SetBinLabel(3,"Fully Merged")
  plot_N_Merged.Draw("HIST")

  plot_N_notMerged.Draw("HIST")
  plot_N_partiallyMerged.Draw("HIST")
  plot_N_fullyMerged.Draw("HIST")
  plot_PT_dijet_no.Draw("HIST")
  plot_ETA_dijet_no.Draw("HIST")
  plot_M_dijet_no.Draw("HIST")
  plot_PT_dijet_partially.Draw("HIST")
  plot_ETA_dijet_partially.Draw("HIST")
  plot_M_dijet_partially.Draw("HIST")
  plot_PT_b_dijet_partially.Draw("HIST")
  plot_ETA_b_dijet_partially.Draw("HIST")
  plot_M_b_dijet_partially.Draw("HIST")
  plot_PT_b_dijet_fully.Draw("HIST")
  plot_ETA_b_dijet_fully.Draw("HIST")
  plot_M_b_dijet_fully.Draw("HIST")
  plot_PT_b_not_used.Draw("HIST")
  plot_ETA_b_not_used.Draw("HIST")
  plot_PT_b_not_used_diff.Draw("HIST")
  plot_ETA_b_not_used_diff.Draw("HIST")
  plot_M_b_not_used_diff.Draw("HIST")
  plot_PT_b_not_used_indiv.Draw("HIST")
  plot_ETA_b_not_used_indiv.Draw("HIST")
  plot_PT_b1b2.Draw("HIST")
  plot_ETA_b1b2.Draw("HIST")
  plot_M_b1b2.Draw("HIST")
  plot_sdPHI_lMET.Draw("HIST")

  b = plot_Eff_mu.GetXaxis()
  b.SetBinLabel(1,"No Cuts")
  b.SetBinLabel(2,"Cut I")
  b.SetBinLabel(3,"Cut II")
  b.SetBinLabel(4,"Cut III")
  b.SetBinLabel(5,"Cut IV")
  b.SetBinLabel(6,"Cut V")
  plot_Eff_mu.Draw("HIST")

  c = plot_Eff_e.GetXaxis()
  c.SetBinLabel(1,"No Cuts")
  c.SetBinLabel(2,"Cut I")
  c.SetBinLabel(3,"Cut II")
  c.SetBinLabel(4,"Cut III")
  c.SetBinLabel(5,"Cut IV")
  c.SetBinLabel(6,"Cut V")
  plot_Eff_e.Draw("HIST")

  plot_Delta_PT_b_alpha_b_beta.Draw("HIST")

  c1.Update()

  plot_deltaR_b1b2.Write()
  plot_PT_leptons.Write()
  plot_ETA_leptons.Write()
  plot_PT_b1.Write()
  plot_MET.Write()
  plot_sdETA_b1b2.Write()
  plot_PT_dijet.Write()
  plot_N_Merged.Write()
  plot_N_notMerged.Write()
  plot_N_partiallyMerged.Write()
  plot_N_fullyMerged.Write()
  plot_PT_dijet_no.Write()
  plot_ETA_dijet_no.Write()
  plot_M_dijet_no.Write()
  plot_PT_dijet_partially.Write()
  plot_ETA_dijet_partially.Write()
  plot_M_dijet_partially.Write()
  plot_PT_b_dijet_partially.Write()
  plot_ETA_b_dijet_partially.Write()
  plot_M_b_dijet_partially.Write()
  plot_PT_b_dijet_fully.Write()
  plot_ETA_b_dijet_fully.Write()
  plot_M_b_dijet_fully.Write()
  plot_PT_b_not_used.Write()
  plot_ETA_b_not_used.Write()
  plot_PT_b_not_used_diff.Write()
  plot_ETA_b_not_used_diff.Write()
  plot_M_b_not_used_diff.Write()
  plot_PT_b_not_used_indiv.Write()
  plot_ETA_b_not_used_indiv.Write()
  plot_PT_b1b2.Write()
  plot_ETA_b1b2.Write()
  plot_M_b1b2.Write()
  plot_sdPHI_lMET.Write()
  plot_Eff_mu.Write()
  plot_Eff_e.Write()
  plot_Delta_PT_b_alpha_b_beta.Write()

  f.Close()

  plot_deltaR_b1b2.Reset("ICESM")
  plot_PT_leptons.Reset("ICESM")
  plot_ETA_leptons.Reset("ICESM")
  plot_PT_b1.Reset("ICESM")
  plot_MET.Reset("ICESM")
  plot_sdETA_b1b2.Reset("ICESM")
  plot_PT_dijet.Reset("ICESM")
  plot_N_Merged.Reset("ICESM")
  plot_N_notMerged.Reset("ICESM")
  plot_N_partiallyMerged.Reset("ICESM")
  plot_N_fullyMerged.Reset("ICESM")
  plot_PT_dijet_no.Reset("ICESM")
  plot_ETA_dijet_no.Reset("ICESM")
  plot_M_dijet_no.Reset("ICESM")
  plot_PT_dijet_partially.Reset("ICESM")
  plot_ETA_dijet_partially.Reset("ICESM")
  plot_M_dijet_partially.Reset("ICESM")
  plot_PT_b_dijet_partially.Reset("ICESM")
  plot_ETA_b_dijet_partially.Reset("ICESM")
  plot_M_b_dijet_partially.Reset("ICESM")
  plot_PT_b_dijet_fully.Reset("ICESM")
  plot_ETA_b_dijet_fully.Reset("ICESM")
  plot_M_b_dijet_fully.Reset("ICESM")
  plot_PT_b_not_used.Reset("ICESM")
  plot_ETA_b_not_used.Reset("ICESM")
  plot_PT_b_not_used_diff.Reset("ICESM")
  plot_ETA_b_not_used_diff.Reset("ICESM")
  plot_M_b_not_used_diff.Reset("ICESM")
  plot_PT_b_not_used_indiv.Reset("ICESM")
  plot_ETA_b_not_used_indiv.Reset("ICESM")
  plot_PT_b1b2.Reset("ICESM")
  plot_ETA_b1b2.Reset("ICESM")
  plot_M_b1b2.Reset("ICESM")
  plot_sdPHI_lMET.Reset("ICESM")
  plot_Eff_mu.Reset("ICESM")
  plot_Eff_e.Reset("ICESM")
  plot_Delta_PT_b_alpha_b_beta.Reset("ICESM")

print("End of data reading")

print("Begin of Data Preparation")
arrs = np.array(arrs)
bkg1 = np.array(arrs[0])
bkg2 = np.array(arrs[1])
bkg3 = np.array(arrs[2])
signal1, signal1_vsize = np.array(arrs[3]), np.shape(np.array(arrs[3]))[0]
signal2, signal2_vsize = np.array(arrs[4]), np.shape(np.array(arrs[4]))[0]
signal3, signal3_vsize = np.array(arrs[5]), np.shape(np.array(arrs[5]))[0]

pred1 = np.concatenate((signal1, bkg1[:int(signal1_vsize/3.0), :], bkg2[:int(signal1_vsize/3.0), :], bkg3[:signal1_vsize - 2*int(signal1_vsize/3.0), :]), axis=0)
pred2 = np.concatenate((signal2, bkg1[:int(signal2_vsize/3.0), :], bkg2[:int(signal2_vsize/3.0), :], bkg3[:signal2_vsize - 2*int(signal2_vsize/3.0), :]), axis=0)
pred3 = np.concatenate((signal3, bkg1[:int(signal3_vsize/3.0), :], bkg2[:int(signal3_vsize/3.0), :], bkg3[:signal3_vsize - 2*int(signal3_vsize/3.0), :]), axis=0)


labels1 = np.zeros(np.shape(pred1)[0])
labels2 = np.zeros(np.shape(pred2)[0])
labels3 = np.zeros(np.shape(pred3)[0])

labels1[:signal1_vsize] = 1
labels2[:signal2_vsize] = 1
labels3[:signal3_vsize] = 1


print("End of Data Preparation")

print("Executing train_test_split...")
trainPredictors_m350, testPredictors_m350, trainLabels_m350, testLabels_m350 = train_test_split(pred1, labels1, test_size=0.25)
trainPredictors_m1000, testPredictors_m1000, trainLabels_m1000, testLabels_m1000 = train_test_split(pred2, labels2, test_size=0.25)
trainPredictors_m3000, testPredictors_m3000, trainLabels_m3000, testLabels_m3000 = train_test_split(pred3, labels3, test_size=0.25)

testPredictors = [testPredictors_m350, testPredictors_m1000, testPredictors_m3000]
testLabels = [testLabels_m350, testLabels_m1000, testLabels_m3000]


logreg_m350_model = bcml_model(make_pipeline(StandardScaler(), LogisticRegression()))
logreg_m350_model.fit(trainPredictors_m350, trainLabels_m350)

logreg_m1000_model = bcml_model(make_pipeline(StandardScaler(), LogisticRegression()))
logreg_m1000_model.fit(trainPredictors_m1000, trainLabels_m1000)

logreg_m3000_model = bcml_model(make_pipeline(StandardScaler(), LogisticRegression()))
logreg_m3000_model.fit(trainPredictors_m3000, trainLabels_m3000)


masses, sig_css, bg_css = get_elijah_ttbarzp_cs()

masses = [350, 1000, 3000]
sig_css = [0.001813, 0.0002066, 3.114E-6]

conv = 10**15/10**12 # conv * lumi (in fb-1)*crossx (im pb) = # of events
lumi = 3000

signal_yields = [conv*lumi*sig_cs for sig_cs in sig_css]
background_yields = [conv*lumi*bg_cs for bg_cs in bg_css]
background_yield = sum(background_yields)

bg_labels = [r"No Higgs B.g. ($pp \; \to \; t\overline{t}b\overline{b} \; \backslash \; h \; \to \; bjj \; \overline{b}\ell\nu \;  b\overline{b}$)",
             r"Higgs B.g. ($pp \; \to \; t\overline{t}h \; \to \; bjj \; \overline{b}\ell\nu \;  b\overline{b}$)",
             r"4 Tops B.g. ($pp \; \to \; t\overline{t}t\overline{t} \; \to \; \overline{b}\ell\nu \;  b\overline{b} \; ...$)"]


sample_masses = np.linspace(masses[0], masses[-1], 500)
sigs_f = scipy.interpolate.interp1d(masses, np.log10(sig_css), kind='quadratic')
new_settings = get_settings()
new_settings['figure.figsize'] = (15,10)
with plt.rc_context(new_settings):
    plt.plot(sample_masses, [10**sigs_f(m) for m in sample_masses], 
             label=r"Signal ($pp \; \to \; t\overline{t}Z' \; \to \; bjj \; \overline{b}\ell\nu \;  b\overline{b}$)")
    for bg_cs, label in zip([bg_css[2], bg_css[0], bg_css[1]], bg_labels):
        plt.plot([350, 3000], [bg_cs]*2, label=r"{}".format(label))
    plt.ylabel('Cross Section (pb)');
    plt.xlabel(r"$Z'$ mass $m_{Z'}$ (GeV)");
    plt.xlim(350, 3000)
    plt.yscale('log')
    plt.legend(bbox_to_anchor=(0,0), loc="lower left")
    plt.savefig('crossx.png', dpi=200, bbox_inches='tight')
    plt.clf()


filename_bgs = entries[:3]

for B, name in zip(background_yields, filename_bgs):
    print(f"Background {name} constitutes {round(B/background_yield,3)}% of the total background cross section.")
print(f"\nTotal backgroundcross section: {sum(bg_css)} pb")


def getTime(form='s'):
    seconds = datetime.now().day * 86400 + datetime.now().hour * 3600 + datetime.now().minute * 60 + datetime.now().second
    if form == 's':
        return seconds
    elif form == 'm':
        return round(seconds/60,3)
    elif form == 'h':
        return round(seconds/3600,3)

logreg_models = [logreg_m350_model, logreg_m1000_model, logreg_m3000_model]


time_before = getTime()

logreg_sigs_nosepbg = [model.significance(signal_yield, background_yield, tpr=model.tpr(testLabels[i], preds=testPredictors[i]), fpr=model.tpr(testLabels[i], preds=testPredictors[i]), sepbg=False) for i, (model, signal_yield) in enumerate(zip(logreg_models, signal_yields))]

for sig, mass in zip(logreg_sigs_nosepbg, masses):
    print(f"Z' mass = {mass} GeV --> logistic regression gives significance of {round(sig, 3)} sigma", "w/o separated backgrounds")
time_after = getTime()
print(f"(Runtime: {time_after - time_before} seconds)")

"""
zp_cs = cross_section_helper(masses, sig_css, bg_css, mass_units='GeV')

max_mass = zp_cs.absolute_max_mass_sens()
logreg_sigs_nosepbg_f = scipy.interpolate.interp1d(masses, np.log10(logreg_sigs_nosepbg), kind='quadratic')

with plt.rc_context(get_settings()):
    plt.plot([max_mass for i in range(2)], np.logspace(-2, 1.5, 2), label=r'Theoretical $5\sigma$ Limit', c='black')
    plt.plot(sample_masses, [5 for m in sample_masses], label=r'5$\sigma$', c='blue')
    plt.plot(sample_masses, [1.645 for m in sample_masses], label=r'90% confidence', c='cornflowerblue')
    plt.plot(
        sample_masses, [10**logreg_sigs_nosepbg_f(m) for m in sample_masses], label='Logistic Regression (No b.g. sep.)', 
        c='red')
    plt.ylabel('Signal Significance');
    plt.xlabel(r"$Z'$ mass $m_{Z'}$ (GeV)");
    plt.yscale('log')
    plt.legend()
"""

background_names = entries[:3]
signal_names_2 = ["m(Z')=350 GeV", "m(Z')=1000 GeV", "m(Z')=3000 GeV"]

with plt.rc_context(get_settings()):
    for i, model in enumerate(logreg_models):
        plt.figure(i)
        bin_edges, sig_bins, bg_bins = model.predict_hist(testPredictors[i], testLabels[i], num_bins=40, sepbg=False)
        plt.bar(bin_edges[:-1], sig_bins, width=np.diff(bin_edges), alpha=0.75, align="edge", label="Signal")
        plt.bar(bin_edges[:-1], bg_bins, width=np.diff(bin_edges), alpha=0.75, align="edge", label="Background")
        plt.yscale('log')
        plt.title('Threshold Optimization for {}'.format(signal_names_2[i]))
        plt.gca().set_ylim(10**-3, 10**2)
        plt.gca().set_xlim(0, 1)
        plt.legend()
        plt.savefig(f'log_reg_m{masses[i]}GeV_hist.png', dpi=200, bbox_inches='tight')
        plt.clf()

time_before = getTime(form='m')
logreg_opt_results_nosepbg = [model.best_threshold(signal_yield, background_yield, testPredictors[i], testLabels[i], sepbg=False) for i, (model, signal_yield) in enumerate(zip(logreg_models, signal_yields))]

logreg_opt_sigs_nosepbg = [result[1] for result in logreg_opt_results_nosepbg]
for sig, mass in zip(logreg_opt_sigs_nosepbg, masses):
    print(f"Z' mass = {mass} GeV --> logistic regression gives optimized sign. of {round(sig, 3)} sigma",
          "w/o separated backgrounds")
time_after = getTime(form='m')
print(f"(Runtime: {round(time_after - time_before,3)} minutes)")


with plt.rc_context(get_settings()):
    for i, (model, result) in enumerate(zip(logreg_models, logreg_opt_results_nosepbg)):
        plt.figure(i)
        bin_edges, sig_bins, bg_bins = model.predict_hist(testPredictors[i], testLabels[i], num_bins=40, sepbg=False)
        plt.bar(bin_edges[:-1], sig_bins, width=np.diff(bin_edges), alpha=0.75, align="edge", label="Signal")
        plt.bar(bin_edges[:-1], bg_bins, width=np.diff(bin_edges), alpha=0.75, align="edge", label="Background")
        plt.plot([0.5]*2, [10**-3, 10**2], label='Default Threshold', c='tab:red')
        plt.plot([result[0]]*2, [10**-3, 10**2], label='Optimized Threshold', c='tab:green')
        plt.yscale('log')
        plt.title('Threshold Optimization for {}'.format(signal_names_2[i]))
        plt.gca().set_ylim(10**-3, 10**2)
        plt.gca().set_xlim(0, 1)
        plt.legend()
        plt.savefig(f'log_reg_m{masses[i]}GeV_opt_hist', dpi=200, bbox_inches='tight')



