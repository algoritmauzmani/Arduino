/*
 Name:		ArduinoSerial.ino
 Created:	7/28/2018 3:46:33 AM
 Author:	Muhammed Eminoğlu
 WebSite:   www.algoritmauzmani.com
*/

/*  Pin                    : Arduino Uno

	Role tetikle pini (in) : 2
	Kırmızı Led + Uç       : 3
	Yeşil Led + Uç         : 4
	Devreli Buzzer + Uç    : 7
*/
//KAPI Kapalı ise 0, açık ise 1 olacak
byte KAPIDURUMU = 0;

//Kapı durumunda değişiklik olmadıysa aynı durum gönderilmesin diye bir değişken
byte SONDURUM = 255;

//Kapıyı Açan Fonksiyon
void KapiAc()
{
	//Kapı kapalı ise ...
	if (KAPIDURUMU == 0)
	{
		//Kırmızı ledi söndürüyoruz
		digitalWrite(2, LOW);
		delay(500);
		//Röleyi tetikliyoruz
		//Roleye low verince tetikleniyor buraya dikkat
		digitalWrite(3, LOW);
		//Yeşil Ledi Yakıyoruz
		digitalWrite(4, HIGH);

		//Buzzer'ı tetikleyen fonksiyon 2 parametre alıyor
		//Kaç kez ses çıkaracağı ve sesin çıkma süresi
		KisaCal(1, 1000);
		//Kapı durumu artık açık
		KAPIDURUMU = 1;
	}
}

//Kapıyı Kapatan fonksiyon
void KapiKapa()
{
	//Röleyi kapalı duruma getiriyoruz. (Elimdeki röle ters mantıkla çalışıyor)
	digitalWrite(2, HIGH);
	delay(500);
	//Yeşil Ledi Söndürüyoruz
	digitalWrite(4, LOW);
	//Kırmızı Ledi Yakıyoruz
	digitalWrite(3, HIGH);
	
	//Buzzer'ı 3 defa 250 milisaniyede bir öttürüyoruz
	KisaCal(3,250);

	//Kapı durumunu kapalı olarak belirtiyoruz
	KAPIDURUMU = 0;
}

//Kapı durumunu serialden yazdıran fonksiyon
void DurumYaz(int i=0)
{
	if (i == 0)
	{
		//Eğer kapının mevcut durumunda değişiklik olduysa buraya girecek
		if (SONDURUM != KAPIDURUMU)
		{
			if (KAPIDURUMU == 0)
			{
				Serial.println("KAPALI");
				SONDURUM = 0;
			}

			else if (KAPIDURUMU == 1)
			{
				Serial.println("ACIK");
				SONDURUM = 1;
			}

		}
	}
	else
	{
		if (KAPIDURUMU == 0)
		{
			Serial.write("KAPALI");
			SONDURUM = 0;
		}

		else if (KAPIDURUMU == 1)
		{
			Serial.write("ACIK");
			SONDURUM = 1;
		}
	}
	
}

//Buzzerı tetikleyen fonksiyon
void KisaCal(int KacDefa, int miliSaniye)
{
	for (int i = 0; i < KacDefa; i++)
	{
		digitalWrite(7, HIGH);
		delay(miliSaniye);
		digitalWrite(7, LOW);
		delay(miliSaniye / 5);
	}
	
	
}

// Setup Fonksiyonumuz, Pin modları burada set ediyoruz.
void setup() {
	Serial.begin(115200);
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(7, OUTPUT);

}

// Esas çalışan fonksiyonumuz, döngümüz, her şeyimiz
void loop() {
	//Eğer seri port üzerinden veri gelirse ilgili fonksiyona yöneliyor.
	if (Serial.available())
		SerialKontrol();

	//Kapının mevcut durumunu seri port üzerinden gönderiyor. 
	//Fonksiyonu incelerseniz, aynı durumu seri port üzerinden tekrar tekrar
	//Göndermesini engellediğimizi görürsünüz.
	DurumYaz();
}

//Seri porttan gelen veriyi handle eder.
void SerialKontrol()
{
	while (Serial.available())
	{
		String Gelen = Serial.readString();

		if (Gelen == "AC")
			KapiAc();
		else if (Gelen == "KAPA")
			KapiKapa();
		DurumYaz(1);

	}
}
