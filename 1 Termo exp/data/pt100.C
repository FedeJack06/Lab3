void pt100(){
    int freq_quadra = 10;
    int n_point = 1000;
    double dt = 0.1;
    double VImpulso , t, VRes, VSbarra;
    double somma = 0;
    double I = 0.0009;
    double TRes;
    double R;
    ifstream file("TOT_4.lvm");

    auto tens = new TGraphErrors();
    auto pt100 = new TGraphErrors();


    int i = 1;
    int n = 0;
    while (file >> VImpulso >> t >> VRes >> VSbarra)
    {
        if (VRes >= 0.09178)
        {
            somma += VRes;
            if (i%10 == 0)
            {
                double VMedio = somma/10;
                R = (VMedio/I);
                TRes = 14e-04*pow(R,2) + 2.2959 * R + 29.77;
                pt100->SetPoint(n,t,TRes);
                somma = 0;
                n++;
            }
            tens->SetPoint(i-1,t,VRes);
            i++;
        }
    }

    auto c1 = new TCanvas();
    auto c2 = new TCanvas();
    c1->cd();
    tens->SetMarkerStyle(20);
    tens->Draw("AP");
    c2->cd();
    pt100->SetMarkerStyle(20);
    pt100->Draw("ALP");
    //pt100->Print();
};