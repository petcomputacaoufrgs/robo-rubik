using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using RubikCube;

namespace ArduinoCommunication
{
    public class ArduinoChannel
    {
        #region Serial Port Config Constants
        private const int BAUD_RATE = 9600;
        #endregion

        #region Private Properties
        private SerialPort serialPort { get; set; }
        private bool portCreated { get; set; }
        private bool inVisualization { get; set; }
        private bool inExecution { get; set; }
        #endregion

        public ArduinoChannel(String portName, int baudRate)
        {
            inVisualization = false;
            inExecution = false;
            portCreated = false;
            try
            {
                serialPort = new SerialPort(portName, BAUD_RATE);
                portCreated = true;

            }
            catch (System.IO.IOException exception)
            {
                System.Console.Write("Error: " + exception.Message);
                System.Console.Write("Could not create serial port '" + portName + "'");
            }
        }

        /// <summary>
        /// Verifies if the port could be opened
        /// </summary>
        /// <returns>If the port is opened correctly or not</returns>
        public bool isPortOpen()
        {
            return portCreated;
        }

        /// <summary>
        /// Sends a list of commands to Arduino
        /// </summary>
        /// <returns>Returns true if the list was sent</returns>
        public bool SendMovements(List<Movement> movements)
        {
            if (inExecution)
            {
                int numberOfMoviments = movements.Count;
                if (numberOfMoviments == 0)
                    return false;

                // monta o buffer com os movimentos
                byte[] buffer = ArduinoProtocol.CrateMovements(movements);

                try
                {
                    serialPort.Write(buffer, 0, buffer.Length);
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send the movements.");
                    return false;
                }
                return true;
            }
            return false;
        }

        /// <summary>
        /// Sends the command to init the process of Visualization to Arduino
        /// </summary>
        /// <returns>Returns true if the command was sent</returns>
        public bool SendInitVision()
        {
            if (portCreated)
            {
                byte[] buffer = ArduinoProtocol.CreateInitVisualization();

                try
                {
                    serialPort.Write(buffer, 0, buffer.Length);
                    return true;
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send 'Init Visualization' command.");
                    return false;
                }
            }
            return false;
        }

        /// <summary>
        /// Sends the command to finish the process of Visualization to Arduino.
        /// </summary>
        /// <returns></returns>
        public bool SendFinishVision()
        {
            if (inVisualization)
            {
                byte[] buffer = ArduinoProtocol.CreateFinishVisualization();

                try
                {
                    serialPort.Write(buffer, 0, buffer.Length);
                    inVisualization = false;
                    return true;
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send 'Finish Visualization' command.");
                    return false;
                }
            }
            return false;
        }

        /// <summary>
        /// Sends the command to finish the process of Visualization to Arduino.
        /// </summary>
        /// <returns></returns>
        public bool SendFinishExecution()
        {
            if (inExecution)
            {
                byte[] buffer = ArduinoProtocol.CreateFinishExecution();

                try
                {
                    serialPort.Write(buffer, 0, buffer.Length);
                    inExecution = false;
                    return true;
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send 'Finish Execution' command.");
                    return false;
                }
            }
            return false;
        }

        /// <summary>
        /// Sends the command to init the process of Execution to Arduino
        /// </summary>
        /// <returns>Returns true if the command was sent</returns>
        public bool SendInitExecution()
        {
            if (portCreated)
            {
                byte[] buffer = ArduinoProtocol.CreateInitExecution();

                try
                {
                    serialPort.Write(buffer, 0, buffer.Length);
                    return true;
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send 'Init Execution' command.");
                    return false;
                }
            }
            return false;
        }

        public bool SendVisualizationMovement(RotateCubeMovement movement)
        {
            if (inVisualization)
            {
                byte[] buffer = new byte[1];
                buffer[0] = ArduinoProtocol.CreateMovement(movement);

                try
                {
                    serialPort.ReadExisting();
                    serialPort.Write(buffer, 0, buffer.Length);
                    serialPort.ReadByte();
                    return true;
                }
                catch (Exception e)
                {
                    System.Console.Write("Could not send 'Init Execution' command.");
                    return false;
                }
            }
            return false;
        }
    }
}
