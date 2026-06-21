#include <bits/stdc++.h>
using namespace std;
using node_jalur = pair<int, string>;
using priority_queue_min = priority_queue<node_jalur, vector<node_jalur>, greater<node_jalur>>;

struct pohon_struktur {
    string pucuk_pimpinan;
    unordered_map<string, vector<string>> daftar_bawahan;
};

struct profil_mahasiswa {
    string nama_lengkap, nim, kata_sandi, prodi;
    int semester;
};

struct sesi_konsultasi {
    int id_antrian;
    string nim_mhs, nama_mhs, nama_dosen, waktu;
};

unordered_map<string, profil_mahasiswa> db_akun;
unordered_map<string, vector<pair<string, int>>> peta_graph;

stack<string> tumpukan_krs;
queue<sesi_konsultasi> antrian_dosen;
priority_queue_min antrian_layanan;
list<string> log_sistem;
pohon_struktur hierarki_kampus;

bool status_login = false;
profil_mahasiswa pengguna_aktif;

void bersihkan_layar() {
    system("clear || cls");
}

void tahan_layar() {
    cout << "\n[ Tekan Enter untuk melanjutkan... ]";
    cin.ignore();
    cin.get();
}

void cetak_tiket_konsul(sesi_konsultasi tiket) {
    cout << " +----------------------------------+\n";
    cout << " | TIKET KONSULTASI                 |\n";
    cout << " +----------------------------------+\n";
    cout << " | ID Antrian : " << tiket.id_antrian << "\n";
    cout << " | Nama Mhs   : " << tiket.nama_mhs << "\n";
    cout << " | NIM        : " << tiket.nim_mhs << "\n";
    cout << " | Dosen      : " << tiket.nama_dosen << "\n";
    cout << " | Waktu      : " << tiket.waktu << "\n";
    cout << " +----------------------------------+\n";
}

void tambah_posisi_organisasi(pohon_struktur &pohon) {
    string atasan;
    string jabatan_baru;
    
    cout << " Atasan (Parent) : ";
    cin.ignore();
    getline(cin, atasan);

    cout << " Jabatan (Child) : ";
    getline(cin, jabatan_baru);

    pohon.daftar_bawahan[atasan].push_back(jabatan_baru);
    cout << "\n [+] " << jabatan_baru << " ditambahkan di bawah " << atasan << ".\n";
    log_sistem.push_back("Tambah Jabatan: " + jabatan_baru);
}

void bersihkan_sub_tree(pohon_struktur &pohon, const string &target) {
    if (pohon.daftar_bawahan.find(target) != pohon.daftar_bawahan.end()) {
        vector<string> anak_anak = pohon.daftar_bawahan[target];
        for (auto &anak : anak_anak) {
            bersihkan_sub_tree(pohon, anak);
        }
        pohon.daftar_bawahan.erase(target);
    }
}

void hapus_posisi_organisasi(pohon_struktur &pohon) {
    string target_hapus;
    cout << " Posisi yang akan dihapus: ";
    cin.ignore();
    getline(cin, target_hapus);

    if (target_hapus == pohon.pucuk_pimpinan) {
        pohon.pucuk_pimpinan.clear();
    }

    for (auto &pasangan : pohon.daftar_bawahan) {
        auto &list_anak = pasangan.second;
        for (size_t i = 0; i < list_anak.size(); i++) {
            if (list_anak[i] == target_hapus) {
                list_anak.erase(list_anak.begin() + i);
                break;
            }
        }
    }
    
    bersihkan_sub_tree(pohon, target_hapus);
    cout << "\n [-] " << target_hapus << " beserta jajarannya telah dihapus.\n";
    log_sistem.push_back("Hapus Jabatan: " + target_hapus);
}

void cetak_pohon(pohon_struktur &pohon, const string &node_sekarang, const string &prefix, bool is_last, bool is_root = false) {
    if (is_root == true) {
        cout << " " << node_sekarang << "\n";
    } else {
        if (is_last == true) {
            cout << " " << prefix << "'--- " << node_sekarang << "\n";
        } else {
            cout << " " << prefix << "|--- " << node_sekarang << "\n";
        }
    }

    auto iterator = pohon.daftar_bawahan.find(node_sekarang);
    if (iterator == pohon.daftar_bawahan.end() || iterator->second.empty()) {
        return;
    }

    string prefix_baru = prefix;
    if (is_root == false) {
        if (is_last == true) {
            prefix_baru += "     ";
        } else {
            prefix_baru += "|    ";
        }
    }

    auto &anak_anak = iterator->second;
    for (size_t i = 0; i < anak_anak.size(); i++) {
        bool status_last = false;
        if (i == anak_anak.size() - 1) {
            status_last = true;
        }
        cetak_pohon(pohon, anak_anak[i], prefix_baru, status_last);
    }
}

void set_root_organisasi(pohon_struktur &pohon) {
    string pucuk;
    cout << " Masukkan pimpinan tertinggi (Root): ";
    cin.ignore();
    getline(cin, pucuk);

    pohon.pucuk_pimpinan = pucuk;
    cout << "\n [+] Root organisasi diset ke: " << pohon.pucuk_pimpinan << "\n";
    log_sistem.push_back("Inisiasi Root: " + pucuk);
}

void inisialisasi_data_awal() {
    profil_mahasiswa mhs1;
    mhs1.nama_lengkap = "Hilmy Fausta";
    mhs1.nim = "2101";
    mhs1.kata_sandi = "1234";
    mhs1.prodi = "Informatika";
    mhs1.semester = 4;
    db_akun["hilmy"] = mhs1;

    profil_mahasiswa mhs2;
    mhs2.nama_lengkap = "Julianda Caesar";
    mhs2.nim = "2102";
    mhs2.kata_sandi = "1234";
    mhs2.prodi = "Sistem Informasi";
    mhs2.semester = 4;
    db_akun["julian"] = mhs2;
    
    peta_graph["Gerbang_Utama"].push_back({"Gedung_Rektorat", 3});
    peta_graph["Gerbang_Utama"].push_back({"Fakultas_Teknik", 2});
    
    peta_graph["Gedung_Rektorat"].push_back({"Gerbang_Utama", 3});
    peta_graph["Gedung_Rektorat"].push_back({"Perpustakaan", 2});
    
    peta_graph["Fakultas_Teknik"].push_back({"Gerbang_Utama", 2});
    peta_graph["Fakultas_Teknik"].push_back({"Perpustakaan", 1});
    peta_graph["Fakultas_Teknik"].push_back({"Kantin", 3});
    
    peta_graph["Perpustakaan"].push_back({"Gedung_Rektorat", 2});
    peta_graph["Perpustakaan"].push_back({"Fakultas_Teknik", 1});
    peta_graph["Perpustakaan"].push_back({"Lab_Komputer", 3});
    
    peta_graph["Kantin"].push_back({"Fakultas_Teknik", 3});
    peta_graph["Kantin"].push_back({"Lab_Komputer", 1});
    
    peta_graph["Lab_Komputer"].push_back({"Perpustakaan", 3});
    peta_graph["Lab_Komputer"].push_back({"Kantin", 1});

    hierarki_kampus.pucuk_pimpinan = "Rektor";
    hierarki_kampus.daftar_bawahan["Rektor"].push_back("Dekan_Teknik");
    hierarki_kampus.daftar_bawahan["Rektor"].push_back("Dekan_Sistem_Informasi");
    hierarki_kampus.daftar_bawahan["Dekan_Teknik"].push_back("Departemen_Zenitron");
    hierarki_kampus.daftar_bawahan["Dekan_Teknik"].push_back("Lab_Komputer");
}

void menu_riwayat() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |        RIWAYAT AKTIVITAS         |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Hapus riwayat terakhir        |\n";
        cout << " | 2. Bersihkan semua log           |\n";
        cout << " | 3. Lihat log sistem              |\n";
        cout << " | 4. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 4) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            if (!log_sistem.empty()) {
                log_sistem.pop_back();
                cout << " [+] Log terakhir dihapus.\n";
            } else {
                cout << " [!] Log sudah kosong.\n";
            }
        } else if (opsi == 2) {
            log_sistem.clear();
            cout << " [+] Seluruh log dibersihkan.\n";
        } else if (opsi == 3) {
            if (log_sistem.empty()) {
                cout << " [!] Belum ada aktivitas terekam.\n";
            } else {
                for (const auto &log : log_sistem) {
                    cout << " ~> " << log << "\n";
                }
                cout << " -- [EOF] --\n";
            }
        }
        tahan_layar();
    }
}

void menu_antrian_dosen() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |        ANTRIAN KONSULTASI        |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Ambil Tiket Baru              |\n";
        cout << " | 2. Proses Antrian Depan          |\n";
        cout << " | 3. Cek Posisi Terdepan           |\n";
        cout << " | 4. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 4) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            sesi_konsultasi sesi_baru;
            sesi_baru.id_antrian = antrian_dosen.size() + 1;
            cout << " Nama Mhs     : "; 
            cin.ignore(); 
            getline(cin, sesi_baru.nama_mhs);
            
            cout << " NIM          : "; 
            cin >> sesi_baru.nim_mhs;
            
            cout << " Dosen Tujuan : "; 
            cin.ignore(); 
            getline(cin, sesi_baru.nama_dosen);
            
            cout << " Waktu        : "; 
            getline(cin, sesi_baru.waktu);

            antrian_dosen.push(sesi_baru);
            log_sistem.push_back("Tiket Konsul: " + sesi_baru.nama_mhs);
            cout << " [+] Jadwal berhasil terdaftar!\n";
        } else if (opsi == 2) {
            if (!antrian_dosen.empty()) {
                cout << " Memproses antrian...\n";
                cetak_tiket_konsul(antrian_dosen.front());
                log_sistem.push_back("Proses Konsul: " + antrian_dosen.front().nama_mhs);
                antrian_dosen.pop();
            } else {
                cout << " [!] Antrian kosong.\n";
            }
        } else if (opsi == 3) {
            if (!antrian_dosen.empty()) {
                cetak_tiket_konsul(antrian_dosen.front());
            } else {
                cout << " [!] Antrian kosong.\n";
            }
        }
        tahan_layar();
    }
}

void menu_organisasi() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |     STRUKTUR ORGANISASI TREE     |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Tambah Posisi                 |\n";
        cout << " | 2. Hapus Posisi                  |\n";
        cout << " | 3. Tampilkan Hierarki            |\n";
        cout << " | 4. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 4) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            if (hierarki_kampus.pucuk_pimpinan.empty()) {
                set_root_organisasi(hierarki_kampus);
            } else {
                tambah_posisi_organisasi(hierarki_kampus);
            }
        } else if (opsi == 2) {
            hapus_posisi_organisasi(hierarki_kampus);
        } else if (opsi == 3) {
            if (hierarki_kampus.pucuk_pimpinan.empty()) {
                cout << " [!] Struktur masih kosong.\n";
            } else {
                cetak_pohon(hierarki_kampus, hierarki_kampus.pucuk_pimpinan, "", true, true);
            }
        }
        tahan_layar();
    }
}

void menu_navigasi() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |          PETA NAVIGASI           |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Cari Rute (Dijkstra)          |\n";
        cout << " | 2. Lihat Titik & Koneksi         |\n";
        cout << " | 3. Tambah Titik Peta             |\n";
        cout << " | 4. Buat Jalur Baru               |\n";
        cout << " | 5. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 5) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            string asal;
            string tujuan;
            cout << " Titik Asal   : "; 
            cin >> asal;
            cout << " Titik Tujuan : "; 
            cin >> tujuan;

            if (peta_graph.find(asal) == peta_graph.end() || peta_graph.find(tujuan) == peta_graph.end()) {
                cout << " [!] Koordinat tidak valid.\n";
            } else {
                unordered_map<string, int> jarak;
                unordered_map<string, string> jejak;
                
                for (auto const &[k, v] : peta_graph) {
                    jarak[k] = 1e9;
                }

                priority_queue_min pq;
                jarak[asal] = 0;
                pq.push({0, asal});

                while (!pq.empty()) {
                    string node = pq.top().second;
                    int d = pq.top().first;
                    pq.pop();

                    if (d > jarak[node]) {
                        continue;
                    }

                    for (auto const &tetangga : peta_graph[node]) {
                        string next_node = tetangga.first;
                        int bobot = tetangga.second;

                        if (jarak[node] + bobot < jarak[next_node]) {
                            jarak[next_node] = jarak[node] + bobot;
                            jejak[next_node] = node;
                            pq.push({jarak[next_node], next_node});
                        }
                    }
                }

                if (jarak[tujuan] == 1e9) {
                    cout << " [!] Tidak ada rute ke lokasi tersebut.\n";
                } else {
                    cout << " [+] Rute Ditemukan! (Jarak: " << jarak[tujuan] << ")\n Jalur: ";
                    vector<string> path;
                    string at = tujuan;
                    
                    while (at != "") {
                        path.push_back(at);
                        at = jejak[at];
                    }
                    
                    reverse(path.begin(), path.end());

                    for (size_t i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if (i < path.size() - 1) {
                            cout << " -> ";
                        } else {
                            cout << "\n";
                        }
                    }
                    log_sistem.push_back("Rute: " + asal + " -> " + tujuan);
                }
            }
        } else if (opsi == 2) {
            for (auto const &[asal, tujuan_list] : peta_graph) {
                cout << " [" << asal << "]\n";
                for (auto const &tetangga : tujuan_list) {
                    cout << " |---> " << tetangga.first << " (Jarak: " << tetangga.second << ")\n";
                }
            }
        } else if (opsi == 3) {
            string node_baru;
            cout << " Nama Lokasi: "; 
            cin >> node_baru;
            
            if (peta_graph.find(node_baru) == peta_graph.end()) {
                vector<pair<string, int>> node_kosong;
                peta_graph[node_baru] = node_kosong;
                cout << " [+] Lokasi direkam.\n";
            } else {
                cout << " [!] Lokasi sudah ada.\n";
            }
        } else if (opsi == 4) {
            string node_a;
            string node_b; 
            int bobot;
            cout << " Lokasi A : "; 
            cin >> node_a;
            cout << " Lokasi B : "; 
            cin >> node_b;
            cout << " Jarak    : "; 
            cin >> bobot;
            
            if (peta_graph.find(node_a) != peta_graph.end() && peta_graph.find(node_b) != peta_graph.end()) {
                peta_graph[node_a].push_back({node_b, bobot});
                peta_graph[node_b].push_back({node_a, bobot});
                cout << " [+] Jalur berhasil disambung.\n";
            } else {
                cout << " [!] Salah satu lokasi tidak ada di peta.\n";
            }
        }
        tahan_layar();
    }
}

void menu_krs() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |            SISTEM KRS            |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Input Matkul                  |\n";
        cout << " | 2. Undo Matkul Terakhir          |\n";
        cout << " | 3. Lihat Top Stack               |\n";
        cout << " | 4. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 4) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            string matkul;
            cout << " Kode Matkul: "; 
            cin >> matkul;
            tumpukan_krs.push(matkul);
            log_sistem.push_back("KRS: Tambah " + matkul);
            cout << " [+] " << matkul << " masuk ke draft.\n";
        } else if (opsi == 2) {
            if (!tumpukan_krs.empty()) {
                cout << " [-] Membatalkan: " << tumpukan_krs.top() << "\n";
                log_sistem.push_back("KRS: Undo " + tumpukan_krs.top());
                tumpukan_krs.pop();
            } else {
                cout << " [!] Draft kosong.\n";
            }
        } else if (opsi == 3) {
            if (!tumpukan_krs.empty()) {
                cout << " Matkul terbaru: " << tumpukan_krs.top() << "\n";
            } else {
                cout << " [!] Draft kosong.\n";
            }
        }
        tahan_layar();
    }
}

void menu_prioritas_layanan() {
    int opsi = 0;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |        LAYANAN PRIORITAS         |\n";
        cout << " +----------------------------------+\n";
        cout << " | 1. Ambil Antrian Prioritas       |\n";
        cout << " | 2. Panggil Layanan Teratas       |\n";
        cout << " | 3. Cek Prioritas Utama           |\n";
        cout << " | 4. Kembali                       |\n";
        cout << " +----------------------------------+\n";
        cout << " Pilih opsi: "; 
        cin >> opsi;

        if (opsi == 4) {
            break;
        }

        cout << "\n";
        if (opsi == 1) {
            string nama;
            string jenis;
            cout << " Nama Mhs : "; 
            cin.ignore(); 
            getline(cin, nama);
            cout << " Kategori (Beasiswa / Disabilitas / Akhir / Reguler): "; 
            cin >> jenis;

            int level;
            if (jenis == "Beasiswa") {
                level = 1;
            } else if (jenis == "Disabilitas") {
                level = 2;
            } else if (jenis == "Akhir") {
                level = 3;
            } else {
                level = 4;
            }
            
            antrian_layanan.push({level, nama});
            log_sistem.push_back("Antrian Layanan: " + nama);
            cout << " [+] Masuk sistem prioritas level " << level << ".\n";
        } else if (opsi == 2) {
            if (!antrian_layanan.empty()) {
                cout << " Memanggil: " << antrian_layanan.top().second << "\n";
                antrian_layanan.pop();
            } else {
                cout << " [!] Antrian kosong.\n";
            }
        } else if (opsi == 3) {
            if (!antrian_layanan.empty()) {
                cout << " Prioritas Utama: " << antrian_layanan.top().second << "\n";
            } else {
                cout << " [!] Antrian kosong.\n";
            }
        }
        tahan_layar();
    }
}

void cari_akun() {
    string query;
    while (true) {
        bersihkan_layar();
        cout << " +----------------------------------+\n";
        cout << " |         DIREKTORI AKUN           |\n";
        cout << " +----------------------------------+\n";
        cout << " Username (ketik 'exit' utk batal): "; 
        cin >> query;
        
        if (query == "exit") {
            break;
        }

        auto hasil = db_akun.find(query);
        if (hasil != db_akun.end()) {
            cout << "\n --- DATA DITEMUKAN ---\n";
            cout << " Nama     : " << hasil->second.nama_lengkap << "\n";
            cout << " NIM      : " << hasil->second.nim << "\n";
            cout << " Prodi    : " << hasil->second.prodi << "\n";
            cout << " Semester : " << hasil->second.semester << "\n";
        } else {
            cout << "\n [!] Username tidak terdaftar.\n";
        }
        log_sistem.push_back("Cari Akun: " + query);
        tahan_layar();
    }
}

void proses_login() {
    string uname;
    string sandi;
    bersihkan_layar();
    cout << " === SECURE LOGIN ===\n";
    cout << " Username : "; 
    cin >> uname;
    
    auto cek = db_akun.find(uname);
    if (cek == db_akun.end()) {
        cout << " [!] Username salah!\n";
        tahan_layar();
        return;
    }

    cout << " Password : "; 
    cin >> sandi;
    if (sandi != cek->second.kata_sandi) {
        cout << " [!] Password salah!\n";
        tahan_layar();
        return;
    }

    status_login = true;
    pengguna_aktif = cek->second;
    cout << "\n [+] Login berhasil. Welcome, " << pengguna_aktif.nama_lengkap << "!\n";
    log_sistem.push_back("Login: " + uname);
    tahan_layar();
}

void daftar_akun_baru() {
    profil_mahasiswa mhs_baru;
    string uname;

    bersihkan_layar();
    cout << " === REGISTRASI AKUN ===\n";
    cout << " Username : "; 
    cin >> uname;
    cin.ignore(); 
    
    cout << " Nama     : "; 
    getline(cin, mhs_baru.nama_lengkap); 
    
    cout << " NIM      : "; 
    cin >> mhs_baru.nim;
    cin.ignore(); 

    cout << " Prodi    : "; 
    getline(cin, mhs_baru.prodi);
    
    cout << " Password : "; 
    cin >> mhs_baru.kata_sandi;
    
    cout << " Semester : "; 
    cin >> mhs_baru.semester;

    db_akun[uname] = mhs_baru;
    cout << "\n [+] Registrasi sukses! Silakan login.\n";
    log_sistem.push_back("Registrasi: " + uname);
    tahan_layar();
}

int main() {
    inisialisasi_data_awal();

    while (status_login == false) {
        bersihkan_layar();
        cout << " ==================================\n";
        cout << "      SMART CAMPUS CLI SYSTEM      \n";
        cout << " ==================================\n";
        cout << "  1. Login\n";
        cout << "  2. Register\n";
        cout << " ==================================\n";
        cout << "  Pilih: "; 
        
        int log_or_reg;
        cin >> log_or_reg;

        if (log_or_reg == 1) {
            proses_login();
        } else if (log_or_reg == 2) {
            daftar_akun_baru();
        }
    }

    while (true) {
        bersihkan_layar();
        cout << " ==================================\n";
        cout << "        MAIN DASHBOARD MENU        \n";
        cout << " ==================================\n";
        cout << "  1. Navigasi Peta (Graph)\n";
        cout << "  2. Struktur Organisasi (Tree)\n";
        cout << "  3. Input KRS (Stack)\n";
        cout << "  4. Konsultasi Dosen (Queue)\n";
        cout << "  5. Layanan Prioritas (PQ)\n";
        cout << "  6. Riwayat Log (Linked List)\n";
        cout << "  7. Direktori Mahasiswa (Hash)\n";
        cout << "  8. Logout / Keluar\n";
        cout << " ==================================\n";
        cout << "  Pilih layanan: "; 
        
        int menu;
        cin >> menu;

        switch (menu) {
            case 1: 
                menu_navigasi(); 
                break;
            case 2: 
                menu_organisasi(); 
                break;
            case 3: 
                menu_krs(); 
                break;
            case 4: 
                menu_antrian_dosen(); 
                break;
            case 5: 
                menu_prioritas_layanan(); 
                break;
            case 6: 
                menu_riwayat(); 
                break;
            case 7: 
                cari_akun(); 
                break;
            case 8: 
                bersihkan_layar();
                cout << "Sesi ditutup. Goodbye!\n";
                return 0;
            default:
                cout << " [!] Input tidak valid.\n";
                tahan_layar();
        }
    }
    return 0;
}