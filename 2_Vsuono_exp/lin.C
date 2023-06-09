{
   string fileName = "suono";
   
   /* controllo che il file esista e sia leggibile */
   ifstream inputfile(fileName); 
   if (!inputfile.good()) {  
      cout << "Impossibile leggere il file: " << fileName << endl;
      return;
   }

   TGraphErrors* gr = new TGraphErrors;
   int i = 0;
   double x, y, ex, ey;
   string uno, due, tre, quattro;
   inputfile >> uno >> due >> tre >> quattro;
   while (inputfile >> x >> y >> ex >> ey ) {
      gr->SetPoint(i, x, y);
      gr->SetPointError(i, 0.000001, 0.003);
      i++;
   }

   
   // Calcolo dell'intervallo di definizione della funzione a partire dai
   // dati contenuti nel grafico
   double xMin = TMath::MinElement(gr->GetN(), gr->GetX());
   double xMax = TMath::MaxElement(gr->GetN(), gr->GetX());
   double clearance = 0.1*(xMax - xMin);
   xMin -= clearance;
   xMax += clearance;

   
   /*
    * Definizione della funzione ed inizializzazione dei parametri
    *
    *
    * Alcuni esempi di funzioni:
    *
    * "[0] + [1]*x"           --> polinomio di primo grado, 2 parametri
    *
    * "[0] + [1]*x + [2]*x*x" --> polinomio di secondo grado, 3 parametri
    *
    * "[0]*exp(-[1]*x)"       --> esponenziale decrescente, 2 parametri
    *
    * "[0]*sin([1]*x - [2])"   --> funzione armonica di ampiezza, frequenza
    *                              e fase configurabili, 3 parametri
    */
   TF1 f("f","[0]+x*[1]", xMin, xMax);
   f.SetParameter(0,0);
   f.SetParameter(1,1);

   /* plot dei dati */
   gStyle->SetOptFit(1011);
   TCanvas c1("c1","canvas1",1920,1080);
   c1.cd();
   gr->Draw("AP");
   gr->SetTitle("distanza vs tempo percorrenza");
   gr->GetXaxis()->SetTitle("tempo percorrenza [s]");
   gr->GetYaxis()->SetTitle("distanza microfoni [m]");

   // Fit con la funzione f (che viene automaticamente graficata sui dati)
<<<<<<< HEAD
   gr.Fit("f");
};
=======
   gr->Fit("f");
   c1.Modified(); 
   c1.Update();

   TPaveStats* st = (TPaveStats*)gr->FindObject("stats");
   st->SetX1NDC(0.15); 
   st->SetX2NDC(0.55); 


   //gr->GetListOfFunctions()->Clear(); // remove the "MC" box
   //gr->SetStats(kFALSE); // prevent the "stats" box

   c1.Modified(); 
   c1.Update();


   
}
>>>>>>> d205f121c1fcf41abbeeb8f4859fcc1088c77b5d
