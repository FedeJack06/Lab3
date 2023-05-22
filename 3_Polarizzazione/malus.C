//Grafico e fit con cos^2

void malus(){

    ifstream file("dati.dat");
    double Iout,theta;

    auto gr = new TGraphErrors();
    int i = 0;
    while (file >> theta >>Iout)
    {
        gr->SetPoint(i, theta, Iout);
        double e = 2*TMath::Pi()/100;
        gr->SetPointError(i,Iout*0.1,e);
        i++;
    }

    auto f1 = new TF1("f1","[0]*pow(cos(x-[1]),2)",0.,0.);
    f1->SetParameters(2.3,2);
    gStyle->SetOptFit(1011);
    gr->SetMarkerStyle(20);
    gr->Draw("AP");
    gr->SetTitle("Iout vs angolo polarizzatore");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("intensita in uscita []");

    gr->Fit("f1");

};


