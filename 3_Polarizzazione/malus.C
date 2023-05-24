//Grafico e fit con cos^2
//72  0.050   3e-4
//77  0.049   3e-4

//0.125 0.0451397
void malus(){

    ifstream file("ottavo.dat");
    double Iout,theta,eI;
    double e = 2*TMath::Pi()/100;

    auto gr = new TGraphErrors();
    int i = 0;
    while (file >> theta >> Iout >> eI)
    {
        gr->SetPoint(i, (theta-52)*2*TMath::Pi()/100, Iout);
        gr->SetPointError(i,e/sqrt(3),eI);
        i++;
    }

    //auto f1 = new TF1("f1","[0]*pow(cos(x-[1]),2)",0.,0.);
    auto f1 = new TF1("f1","[0]*pow(cos(x-[1]),2)+[2]",0.,0.);
    f1->SetParameters(0.3,0.1,0.01);
    gStyle->SetOptFit(1011);
    gr->SetMarkerStyle(20);
    gr->Draw("AP");
    gr->SetTitle("Iout vs angolo polarizzatore");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("intensita in uscita []");

    gr->Fit("f1");
    cout << "massimo della funzione: " << f1->GetMaximumX(-0.6,0.6,1e-4) << endl;
    //gr->Print();
};


