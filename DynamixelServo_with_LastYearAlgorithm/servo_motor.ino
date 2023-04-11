/** 
 * fungsi mendapatkan sudut sebenarnya dari servo 
 * servoTujuan diisi dengan kode LFT, LBT, RFT, dst
 * nilai diisi dengan sudut yang diinginkan
 */
int SudutReal(String servoTujuan, int nilai) {
  int nilaiReal;
  
  if (servoTujuan.equals("LFT")) {//-35 s/d 43
    nilaiReal = (lftTegak - NilaiBatas(nilai, -35, 43));
  } else if (servoTujuan.equals("LBT")) {//-40 s/d 32
    nilaiReal = (lbtTegak - NilaiBatas(nilai, -40, 32));
  } else if (servoTujuan.equals("RFT")) {//-35 s/d 43
    nilaiReal = (rftTegak + NilaiBatas(nilai, -35, 43));
  } else if (servoTujuan.equals("RBT")) {//-40 s/d 32
    nilaiReal = (rbtTegak + NilaiBatas(nilai, -40, 32));
  } else if (servoTujuan.equals("LFM")) {//-28 s/d 50
    nilaiReal = (lfmTegak - NilaiBatas(nilai, -28, 50));
  } else if (servoTujuan.equals("LBM")) {//-28 s/d 50
    nilaiReal = (lbmTegak - NilaiBatas(nilai, -28, 50));
  } else if (servoTujuan.equals("RFM")) {//-28 s/d 50
    nilaiReal = (rfmTegak + NilaiBatas(nilai, -28, 50));
  } else if (servoTujuan.equals("RBM")) {//-28 s/d 50
    nilaiReal = (rbmTegak + NilaiBatas(nilai, -28, 50));
  } else if (servoTujuan.equals("LFB")) {//-51 s/d 44
    nilaiReal = (lfbTegak + NilaiBatas(nilai, -51, 44));
  } else if (servoTujuan.equals("LBB")) {//-51 s/d 44
    nilaiReal = (lbbTegak + NilaiBatas(nilai, -51, 44));
  } else if (servoTujuan.equals("RFB")) {//-51 s/d 44
    nilaiReal = (rfbTegak - NilaiBatas(nilai, -51, 44));
  } else if (servoTujuan.equals("RBB")) {//-51 s/d 44
    nilaiReal = (rbbTegak - NilaiBatas(nilai, -51, 44));
  } else {//kondisi error akan terjadi robot berdiri selama 2 detik
    Berdiri();
    delay(2000);
  }
  return nilaiReal;
}


/**
 * fungsi untuk menggerakkan servo dan sekaligus menyimpan sudut servo saat ini
 */
void ServoWrite(String servoNama, int sudut) {
  Servo servoPakai;
  if (servoNama.equals("LFT")) {
    servoPakai=servoLFT;  posisiLFT=sudut;
  } else if (servoNama.equals("LFM")) {
    servoPakai=servoLFM;  posisiLFM=sudut;
  } else if (servoNama.equals("LFB")) {
    servoPakai=servoLFB;  posisiLFB=sudut;
  
  } else if (servoNama.equals("LBT")) {
    servoPakai=servoLBT;  posisiLBT=sudut;
  } else if (servoNama.equals("LBM")) {
    servoPakai=servoLBM;  posisiLBM=sudut;
  } else if (servoNama.equals("LBB")) {
    servoPakai=servoLBB;  posisiLBB=sudut;
  
  } else if (servoNama.equals("RFT")) {
    servoPakai=servoRFT;  posisiRFT=sudut;
  } else if (servoNama.equals("RFM")) {
    servoPakai=servoRFM;  posisiRFM=sudut;
  } else if (servoNama.equals("RFB")) {
    servoPakai=servoRFB;  posisiRFB=sudut;
  
  } else if (servoNama.equals("RBT")) {
    servoPakai=servoRBT;  posisiRBT=sudut;
  } else if (servoNama.equals("RBM")) {
    servoPakai=servoRBM;  posisiRBM=sudut;
  } else if (servoNama.equals("RBB")) {
    servoPakai=servoRBB;  posisiRBB=sudut;
  }
  
  servoPakai.write(SudutReal(servoNama,sudut));
}


/**
 * Fungsi mendapatkan sudut saat ini dari servo
 */
int ServoPosisi(String servoNama) {
  if (servoNama.equals("LFT")) return posisiLFT;
  else if (servoNama.equals("LFM")) return posisiLFM;
  else if (servoNama.equals("LFB")) return posisiLFB;
  
  else if (servoNama.equals("LBT")) return posisiLBT;
  else if (servoNama.equals("LBM")) return posisiLBM;
  else if (servoNama.equals("LBB")) return posisiLBB;
  
  else if (servoNama.equals("RFT")) return posisiRFT;
  else if (servoNama.equals("RFM")) return posisiRFM;
  else if (servoNama.equals("RFB")) return posisiRFB;
  
  else if (servoNama.equals("RBT")) return posisiRBT;
  else if (servoNama.equals("RBM")) return posisiRBM;
  else if (servoNama.equals("RBB")) return posisiRBB;
}
