
// E' un banalissimo fit lineare
// **********************************************************

void attOtt(){

    ifstream file("conc.dat");
    double conc,angolo;
    auto gr = new TGraphErrors();
    double e = 2*TMath::Pi()/100;

    int i = 0;
    while (file >> conc >> angolo)
    {
        gr->SetPoint(i, angolo, conc);
        gr->SetPointError(i, 0, e);
        i++;
    }

    auto f = new TF1("f","[0]+[1]*(x)",0.,0.);
    f->SetParameters(0,1);

    gStyle->SetOptFit(1011);
    gr->SetMarkerStyle(20);
    gr->Draw("AP");
    gr->SetTitle("Concentrazione di glucosio vs angolo di rotazione polarizzazione");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("Concentrazione relativa []");

    gr->Fit("f");
};