using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace VisualStudioProgram
{
    public partial class Form1 : Form
    {
        #region Serial Port Config Constants
        private const int BAUD_RATE = 9600;
        #endregion

        #region Private Properties
        private SerialPort serialPort { get; set; }
        private byte state0 = reset;
        private byte state1 = reset;
        private byte state2 = reset;
        private byte state3 = reset;
        private byte state4 = reset;
        #endregion

       

        #region Protocol Constants
        private const byte juiz = 0;
        private const byte pause = 1;
        private const byte start = 2;
        private const byte reset = 3;
        private const byte btnPress = 4;
        private const byte btnNotPress = 5;
        private const byte fim = 255;
        private const byte ativo = 1;
        private const byte inativo = 0;
        private const byte mod0 = 128;
        private const byte mod1 = 129;
        private const byte mod2 = 130;
        private const byte mod3 = 131;
        private const byte mod4 = 132;
        #endregion

        public Form1()
        {
            InitializeComponent();
        }

        private void Send(byte[] buff)
        {
            if (radioButtonConected.Checked)
            {
                serialPort.Write(buff, 0, buff.Length);
            }

        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort = new SerialPort(txtPortName.Text, BAUD_RATE);
                radioButtonConected.Checked = true;

            }
            catch (System.IO.IOException exception)
            {
                radioButtonConected.Checked = false;
                System.Console.Write("Error: " + exception.Message);
                System.Console.Write("Could not create serial port '" + txtPortName.Text + "'");
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// Envia um comando de ativo para a arduino (modulo,Ativo,estado,fim)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Ativo0_CheckedChanged(object sender, EventArgs e)
        {           
            byte[] buff = new byte[4];
            buff[0] = mod0;
            buff[1] = (Ativo0.Checked ? ativo : inativo);
            buff[2] = state0;
            buff[3] = fim;
            Send(buff);            
        }
    }
}
