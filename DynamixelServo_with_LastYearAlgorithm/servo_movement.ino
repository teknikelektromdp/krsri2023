/**
 * fungsi keadaan awal robot (kondisi berdiri)
 * semua sudut bernilai nol
 */
void Berdiri(){
  ServoWrite("LFT",0);  ServoWrite("RFT",0);
  ServoWrite("LBT",0);  ServoWrite("RBT",0);

  ServoWrite("LFM",0);  ServoWrite("RFM",0);
  ServoWrite("LBM",0);  ServoWrite("RBM",0);

  ServoWrite("LFB",0);  ServoWrite("RFB",0);
  ServoWrite("LBB",0);  ServoWrite("RBB",0);
}


int berdiriLftNaik=0, berdiriRftNaik=0,
    berdiriLbtNaik=0, berdiriRbtNaik=0,
    berdiriLfmNaik=10, berdiriRfmNaik=10,
    berdiriLbmNaik=-28, berdiriRbmNaik=-28,
    berdiriLfbNaik=-10, berdiriRfbNaik=-10,
//    berdiriLbbNaik=28, berdiriRbbNaik=28;
    berdiriLbbNaik=10, berdiriRbbNaik=10;

void BerdiriNaik(){
  ServoWrite("LFT",BerdiriSudut("LFT", 0));  ServoWrite("RFT",BerdiriSudut("RFT", 0));
  ServoWrite("LBT",BerdiriSudut("LBT", 0));  ServoWrite("RBT",BerdiriSudut("RBT", 0));

  ServoWrite("LFM",BerdiriSudut("LFM", 0));  ServoWrite("RFM",BerdiriSudut("RFM", 0));
  ServoWrite("LBM",BerdiriSudut("LBM", 0));  ServoWrite("RBM",BerdiriSudut("RBM", 0));

  ServoWrite("LFB",BerdiriSudut("LFB", 0));  ServoWrite("RFB",BerdiriSudut("RFB", 0));
  ServoWrite("LBB",BerdiriSudut("LBB", 0));  ServoWrite("RBB",BerdiriSudut("RBB", 0));
}

int BerdiriSudut(String servoNama, int sudut) {
  if (servoNama.equals("LFT")) return sudut+berdiriLftNaik;
  else if (servoNama.equals("LFM")) return sudut+berdiriLfmNaik;
  else if (servoNama.equals("LFB")) return sudut+berdiriLfbNaik;
  
  else if (servoNama.equals("LBT")) return sudut+berdiriLbtNaik;
  else if (servoNama.equals("LBM")) return sudut+berdiriLbmNaik;
  else if (servoNama.equals("LBB")) return sudut+berdiriLbbNaik;
  
  else if (servoNama.equals("RFT")) return sudut+berdiriRftNaik;
  else if (servoNama.equals("RFM")) return sudut+berdiriRfmNaik;
  else if (servoNama.equals("RFB")) return sudut+berdiriRfbNaik;
  
  else if (servoNama.equals("RBT")) return sudut+berdiriRbtNaik;
  else if (servoNama.equals("RBM")) return sudut+berdiriRbmNaik;
  else if (servoNama.equals("RBB")) return sudut+berdiriRbbNaik;
}


/**
 * Fungsi menggerakkan servo dengan perlahan
 */
void ServoMovementSingle(String servoNama, int sudutBaru) {
  int sudutLama, pengali, jarak;
  
  sudutLama=ServoPosisi(servoNama);
  jarak=HitungJarak(sudutLama, sudutBaru);
  pengali=HitungPengali(sudutLama, sudutBaru);

  for (int i=1; i<=jarak; i++) {
    ServoWrite(servoNama, sudutLama + (pengali * i));
    delay(delayWaktu);
  }
}

void ServoMovementDouble(
  String servoNama1, int sudutBaru1, 
  String servoNama2, int sudutBaru2
) {
  int sudutLama1, pengali1, jarak1,
      sudutLama2, pengali2, jarak2,
      sudutTemp1, sudutTemp2, minimum, maksimum;
      
  sudutLama1=ServoPosisi(servoNama1);
  sudutLama2=ServoPosisi(servoNama2);
//  Serial.print("DoubleB1 ");Serial.println(servoNama2 + " " + ServoPosisi(servoNama2) + " | " + sudutBaru2);

  jarak1=HitungJarak(sudutLama1, sudutBaru1);
  pengali1=HitungPengali(sudutLama1, sudutBaru1);

  jarak2=HitungJarak(sudutLama2, sudutBaru2);
  pengali2=HitungPengali(sudutLama2, sudutBaru2);

  //menghitung nilai terkecil dari jarak1 dan jarak2
  minimum=jarak1;
  if (jarak2 < minimum) minimum=jarak2;

  //menghitung nilai terbesar dari jarak1 dan jarak2
  maksimum=jarak1;
  if (jarak2 > maksimum) maksimum=jarak2;
  
  //melakukan pergerakan servo secara bersamaan dari sudutLama ke sudutBaru
  for (int i=1; i<=minimum; i++) {
    sudutTemp1 = sudutLama1 + (pengali1 * i * ((jarak1*1.0)/(minimum*1.0)));
    sudutTemp2 = sudutLama2 + (pengali2 * i * ((jarak2*1.0)/(minimum*1.0)));

    if ((pengali1==1 && sudutTemp1<=sudutBaru1) || (pengali1==-1 && sudutTemp1>=sudutBaru1)) {
      ServoWrite(servoNama1, sudutTemp1);    
//      Serial.println(servoNama1 + " sudutTemp1 " + sudutTemp1);
    }
    if ((pengali2==1 && sudutTemp2<=sudutBaru2) || (pengali2==-1 && sudutTemp2>=sudutBaru2)) {
      ServoWrite(servoNama2, sudutTemp2);
//      Serial.println(servoNama2 + " sudutTemp2 " + sudutTemp2);
    }
    
    delay(((maksimum*1.0)/(minimum*1.0))*delayWaktu);
  }
}

void ServoMovementTriple(
  String servoNama1, int sudutBaru1, 
  String servoNama2, int sudutBaru2,
  String servoNama3, int sudutBaru3
) {
  int sudutLama1, pengali1, jarak1,
      sudutLama2, pengali2, jarak2,
      sudutLama3, pengali3, jarak3,
      sudutTemp1, sudutTemp2, sudutTemp3, minimum, maksimum;
      
  sudutLama1=ServoPosisi(servoNama1);
  sudutLama2=ServoPosisi(servoNama2);
  sudutLama3=ServoPosisi(servoNama3);

  jarak1=HitungJarak(sudutLama1, sudutBaru1);
  pengali1=HitungPengali(sudutLama1, sudutBaru1);

  jarak2=HitungJarak(sudutLama2, sudutBaru2);
  pengali2=HitungPengali(sudutLama2, sudutBaru2);

  jarak3=HitungJarak(sudutLama3, sudutBaru3);
  pengali3=HitungPengali(sudutLama3, sudutBaru3);

  //menghitung nilai terkecil dari jarak1, jarak2, dan jarak3
  minimum=jarak1;
  if (jarak2 < minimum) minimum=jarak2;
  else if (jarak3 < minimum) minimum=jarak3;

  //menghitung nilai terbesar dari jarak1, jarak2, dan jarak3
  maksimum=jarak1;
  if (jarak2 > maksimum) maksimum=jarak2;
  else if (jarak3 > maksimum) maksimum=jarak3;
  
  //melakukan pergerakan servo secara bersamaan dari sudutLama ke sudutBaru
  for (int i=1; i<=minimum; i++) {
    sudutTemp1 = sudutLama1 + (pengali1 * i * ((jarak1*1.0)/(minimum*1.0)));
    sudutTemp2 = sudutLama2 + (pengali2 * i * ((jarak2*1.0)/(minimum*1.0)));
    sudutTemp3 = sudutLama3 + (pengali3 * i * ((jarak3*1.0)/(minimum*1.0)));

    if ((pengali1==1 && sudutTemp1<=sudutBaru1) || (pengali1==-1 && sudutTemp1>=sudutBaru1)) {
      ServoWrite(servoNama1, sudutTemp1);    
    }
    if ((pengali2==1 && sudutTemp2<=sudutBaru2) || (pengali2==-1 && sudutTemp2>=sudutBaru2)) {
      ServoWrite(servoNama2, sudutTemp2);
    }
    if ((pengali3==1 && sudutTemp3<=sudutBaru3) || (pengali3==-1 && sudutTemp3>=sudutBaru3)) {
      ServoWrite(servoNama3, sudutTemp3);
    }
    
    delay(((maksimum*1.0)/(minimum*1.0))*delayWaktu);
  }
}
