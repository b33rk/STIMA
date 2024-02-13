# Tugas Kecil I Strategi Algoritma (IF2211)
## Abdullah Mubarak (13522101)

## Table of Contents
* [Tentang Program](#cyberpunk)
* [Dependencies](#dependencies)
* [Cara Kompilasi](#compilation)
* [How to Use](#how-to-use)

## Cyberpunk 2077 Breach Protocol

Cyberpunk 2077 Breach Protocol adalah minigame meretas pada permainan video Cyberpunk 2077.
Minigame ini merupakan simulasi peretasan jaringan local dari ICE (Intrusion Countermeasures
Electronics) pada permainan Cyberpunk 2077. Komponen pada permainan ini antara lain adalah:
1. Token – terdiri dari dua karakter alfanumerik seperti E9, BD, dan 55.
2. Matriks – terdiri atas token-token yang akan dipilih untuk menyusun urutan kode.
3. Sekuens – sebuah rangkaian token (dua atau lebih) yang harus dicocokkan.
4. Buffer – jumlah maksimal token yang dapat disusun secara sekuensial.

Aturan permainan Breach Protocol antara lain:
1. Pemain bergerak dengan pola horizontal, vertikal, horizontal, vertikal (bergantian) hingga
semua sekuens berhasil dicocokkan atau buffer penuh.
IF2211 Strategi Algoritma – Tugas Kecil 1 1
2. Pemain memulai dengan memilih satu token pada posisi baris paling atas dari matriks.
3. Sekuens dicocokkan pada token-token yang berada di buffer.
4. Satu token pada buffer dapat digunakan pada lebih dari satu sekuens.
5. Setiap sekuens memiliki bobot hadiah atau reward yang variatif.
6. Sekuens memiliki panjang minimal berupa dua token.

## Deskripsi Program <a href="cyberpunk"></a>

Program ini adalah program yang ditulis dalam bahasa C++ yang menggunakan algoritma _brute force_ untuk menemukan sequence paling optimal dari input yang diberikan pada minigame Cyberpunk 2077 Breach Protocol

## Dependencies <a href="dependencies"></a>

g++.exe (GCC) 11.2.0

## Cara Kompilasi Program <a href="compilation"></a>

1. Buka folder bin
2. Pastikan path pada terminal sudah benar
3. Ketik ./main pada command line

## How to Use
1. Clone repository github ke lokal
2. Kompilasi program
3. Masukkan bisa berupa file atau input
4. Jika memilih input `file` maka format `file input` adalah sebagai berikut
    ```
    buffer_size                     
    matrix_widthmatrix_height
    matrix
    number_of_sequences
    sequences_1
    sequences_1_reward
    sequences_2
    sequences_2_reward
    ...
    sequences_n
    sequences_n_reward
    ```
5. Jika memilih input `randomize`, lengkapi bagian kosong seperti contoh berikut:
    ```
    TOKEN AMOUNT: 5
    TOKEN: BD 1C 7A 55 E9
    BUFFER SIZE: 7
    MATRIX SIZE: 6 6
    SEQUENCE AMT: 3
    MAX SEQUENCE: 4
    ```
6. Setelah output keluar, hasil bisa disimpan ke file txt dengan cara memasukkan path file setelah mengetik y, seperti contoh:
    ```
    Apakah ingin menyimpan solusi? (y/n)
    y
    Masukkan nama file: test.txt
    Data berhasil tertulis ke file.
    ```
