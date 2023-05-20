void fit(){

    ifstream file("data.txt");
    double Iout,theta;

    auto gr = new TGraphErrors();
    int i = 0;
    while (file >> theta >>Iout)
    {
        gr->SetPoint(i, Iout , theta);
        gr->SetPointError(i,Iout,2*TMath::Pi/100)
    }

    auto f1 = new TF1("f1","[0]*pow(cos(x-[1]),2)",0.,0.);
    gStyle->SetOptFit(1011);
    gr->Draw("AP");
    gr->SetTitle("Iout vs angolo polarizzatore");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("intensita in uscita []");

    gr->Fit("f1");

};


