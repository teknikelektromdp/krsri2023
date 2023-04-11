/**
 * fungsi membatasi nilai minimum dan maksimum
 */
int NilaiBatas(int nilai, int nilaiMin, int nilaiMax){
  if (nilai>nilaiMax) nilai=nilaiMax;
  else if (nilai<nilaiMin) nilai=nilaiMin;
  return nilai;
}

/**
 * Fungsi hitung jarak sudut lama dengan sudut baru
 */
int HitungJarak(int sudutLama, int sudutBaru) {
  if (sudutLama < sudutBaru) return (sudutBaru-sudutLama);
  else if (sudutLama > sudutBaru) return (sudutLama-sudutBaru);
  else return 0;//untuk sudutLama sama dengan sudutBaru
}

/**
 * Fungsi hitung pengali antara sudut lama dengan sudut baru
 * untuk menentukan pergerakan menaik atau menurun
 */
int HitungPengali(int sudutLama, int sudutBaru) {
  if (sudutLama < sudutBaru) return 1;
  else if (sudutLama > sudutBaru) return -1;
  else return 1;//untuk sudutLama sama dengan sudutBaru  
}
