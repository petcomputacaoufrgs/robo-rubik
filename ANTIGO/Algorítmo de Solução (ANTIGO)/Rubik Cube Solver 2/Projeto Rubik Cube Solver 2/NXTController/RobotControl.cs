using System;
using System.Collections.Generic;
using System.Text;
using AForge.Robotics.Lego;

namespace NXTRobotController
{
    public class RobotControl
    {
        private NXTBrick nBrick = new NXTBrick();

        /// <summary>
        /// The COM port for the connection
        /// </summary>
        public string ComPort { get; set; }

        /// <summary>
        /// Connect to the NXT Robot
        /// </summary>
        /// <returns>Returns a boolean with the connection result</returns>
        public bool Connect()
        {
            return this.Connect(ComPort);
        }

        /// <summary>
        /// Connect to the NXT Robot
        /// </summary>
        /// <param name="comPort">The COM port for the connection</param>
        /// <returns>Returns a boolean with the connection result</returns>
        public bool Connect(string comPort)
        {
            bool retVal = false;
            if (!nBrick.IsConnected)
                retVal = nBrick.Connect(comPort);
            else
                retVal = true;
            return retVal;
        }

        /// <summary>
        /// Disconnect the robot
        /// </summary>
        public void Disconnect()
        {
            nBrick.Disconnect();
        }
    }
}
