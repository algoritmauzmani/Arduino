using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArduinoControl
{
    public partial class Form1 : Form
    {
        delegate void SetKapiDurumu(String text);
        delegate void SetButtonDurumu(String text);

        public Form1()
        {
            InitializeComponent();
        }

        private void SetKapiDurumuText(String text)
        {
            if(lblDurum.InvokeRequired)
            {
                if (text == "AÇIK")
                {
                    lblDurum.ForeColor = System.Drawing.Color.Green;
                }
                    
                else if (text == "KAPALI")
                {
                    lblDurum.ForeColor = System.Drawing.Color.Red;
                }
                    
                SetKapiDurumu d = new SetKapiDurumu(SetKapiDurumuText);
                this.BeginInvoke(d, new object[] { text });
            }
            else
            {
                if (text == "AÇIK")
                    lblDurum.ForeColor = System.Drawing.Color.Green;
                else if (text == "KAPALI")
                    lblDurum.ForeColor = System.Drawing.Color.Red;
                lblDurum.Text = text;
            }
        }

        private void SetButtonDurumuText(String text)
        {
            if (button1.InvokeRequired)
            {
                
                if (text == "AÇ")
                {
                    button1.BackColor = Color.Green;
                }
                else if(text == "KAPA")
                {
                    button1.BackColor = Color.Red;
                }
                SetButtonDurumu d = new SetButtonDurumu(SetButtonDurumuText);
                this.BeginInvoke(d, new object[] { text });
            }
            else
            {
                
                button1.Text = text;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(button1.Text == "AÇ")
            {
                serialPort1.Write("AC");
            }
            else if(button1.Text == "KAPA")
            {
                serialPort1.Write("KAPA");
            }
            
            
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            String Gelen = serialPort1.ReadExisting();
            
            if (Gelen == "ACIK")
            {
                SetKapiDurumuText("AÇIK");
                SetButtonDurumuText("KAPA");
            }
            else if(Gelen == "KAPALI")
            {
                SetKapiDurumuText("KAPALI");
                SetButtonDurumuText("AÇ");

            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            String[] portlar = SerialPort.GetPortNames();
            if(portlar.Length > 0)
            {
                for (int i = 0; i < portlar.Length; i++)
                {
                    comboBox1.Items.Add(portlar[i]);
                }
            }
            else
            {
                comboBox1.Items.Add("Port Bulunamadı");
            }
            comboBox1.SelectedIndex = 0;
            PortaBaglan();
            
            
        }

        void PortaBaglan()
        {
            if(serialPort1.IsOpen != true)
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.BaudRate = 115200;
                serialPort1.Open();
            }     
        }

        private void button2_Click(object sender, EventArgs e)
        {
            PortaBaglan();
        }



        private void button1_Click_1(object sender, EventArgs e)
        {
            if (button1.Text == "AÇ")
            {
                serialPort1.Write("AC");
                
            }
            else if(button1.Text == "KAPA")
            {
                serialPort1.Write("KAPA");
                
            }
            
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            serialPort1.Write("Rastgele");
        }
    }
}
