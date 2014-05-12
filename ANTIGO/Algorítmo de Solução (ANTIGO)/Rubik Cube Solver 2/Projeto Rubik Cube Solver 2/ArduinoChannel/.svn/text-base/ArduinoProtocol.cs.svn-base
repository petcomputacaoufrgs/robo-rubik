using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RubikCube;
using CubeSolver;

namespace ArduinoCommunication
{
    public static class ArduinoProtocol
    {
        #region Movement Bits Mapping
        public const byte ROTATE_CUBE = 0;                     // 0000|0[0]00
        public const byte ROTATE_FACE = 4;                     // 0000|0[1]00
        public const byte TYPE_HALF_RIGHT = 0;                 // 0000|00[00]
        public const byte TYPE_HALF_LEFT = 1;                  // 0000|00[01]
        public const byte TYPE_FULL = 2;                       // 0000|00[10]
        public const byte ANOTHER_COMMAND = 3;                 // 0000|00[11]
        public const byte LEFT_CLAW = 0;                       // 0000|[0]000
        public const byte FRONT_CLAW = 8;                      // 0000|[1]000
        #endregion

        #region Commands Bit Mapping
        public const byte INIT_VISION = 3;                     // 0000|[00]11
        public const byte INIT_EXECUTION = 7;                  // 0000|[01]11
        public const byte NOP = 11;                            // 0000|[10]11
        public const byte END_PROGRAM = 15;                    // 0000|[11]11
        public const byte SHIFT_4_LEFT = 4;                    // 00000100
        #endregion

        #region Movement Convertion Methods
        /// <summary>
        /// Creates a list of bytes to be sent to Arduino that represents the movements to be done
        /// </summary>
        /// <param name="movements">List of movements to be sent to Arduino</param>
        /// <returns>List of bytes representing the movements to be sent to Arduino</returns>
        public static byte[] CrateMovements(List<Movement> movements)
        {
            int numberOfMovements = movements.Count;

            // monta o buffer com os movimentos
            byte[] buffer = new byte[(numberOfMovements + 1) / 2];
            int posBuffer = 0;
            int posMov = 0;
            while (numberOfMovements > 0)
            {
                if (numberOfMovements > 1)
                {
                    buffer[posBuffer] |= CreateMovement(movements[posMov++]);
                    buffer[posBuffer] |= (byte)(CreateMovement(movements[posMov++]) << SHIFT_4_LEFT);
                    numberOfMovements -= 2;
                }
                else
                {
                    buffer[posBuffer] |= CreateMovement(movements[posMov++]);
                    buffer[posBuffer] |= NOP << SHIFT_4_LEFT;
                    numberOfMovements--;
                }
                posBuffer++;
            }

            return buffer;
        }

        /// <summary>
        /// Creates a movement in the right form to Arduino. It uses 4 bits of the less significative bits of a byte.
        /// </summary>
        /// <param name="mov">The movement</param>
        /// <returns>A byte with the 4 less significative bits used to represent a movement.</returns>
        public static byte CreateMovement(Movement mov)
        {
            byte command = 0;

            if (mov.Type.Equals(TurnType.HalfTurnRight))
                command |= TYPE_HALF_RIGHT;
            else if (mov.Type.Equals(TurnType.HalfTurnLeft))
                command |= TYPE_HALF_LEFT;
            else
                command |= TYPE_FULL;

            if (mov is RotateCubeMovement)
            {
                command |= ROTATE_CUBE;
                if (((RotateCubeMovement)mov).Axis.Equals(CoordinateAxis.X))
                    command |= FRONT_CLAW;
                else if (((RotateCubeMovement)mov).Axis.Equals(CoordinateAxis.Y))
                    command |= LEFT_CLAW;
            }
            else if (mov is RotateFaceMovement)
            {
                command |= ROTATE_FACE;
                if (((RotateFaceMovement)mov).PositionFace.Equals(RobotCubeSolver.Claw_F))
                    command |= FRONT_CLAW;
                else if (((RotateFaceMovement)mov).PositionFace.Equals(RobotCubeSolver.Claw_L))
                    command |= LEFT_CLAW;
            }
            return command;
        }

        /// <summary>
        /// Creates a string representation of the bits of the movements (used for tests)
        /// </summary>
        /// <param name="movements">List of momevements to be converted to protocol</param>
        public static String CreateBitRepresentationOfMovements(List<Movement> movements)
        {
            String bitRepresentation = "";

            byte[] convertedMovements = CrateMovements(movements);
            int numberOfBytes = (movements.Count + 1) / 2;

            for (int n = 1; n <= numberOfBytes; n++)
            {
                bitRepresentation += "Byte " + n.ToString() + ": ";
                for (byte mask = 128; mask != 0; mask >>= 1)
                {
                    if ((convertedMovements[n - 1] & mask) != 0)
                    {
                        bitRepresentation += "1 ";
                    }
                    else
                    {
                        bitRepresentation += "0 ";
                    }
                }
                bitRepresentation += "\n";
            }

            return bitRepresentation;
        }
        #endregion

        public static byte[] CreateInitVisualization()
        {
            byte[] buffer = new byte[1];

            buffer[0] = ArduinoProtocol.NOP;
            buffer[0] <<= ArduinoProtocol.SHIFT_4_LEFT;
            buffer[0] |= ArduinoProtocol.INIT_VISION;

            return buffer;
        }

        public static byte[] CreateFinishVisualization()
        {
            byte[] buffer = new byte[1];

            buffer[0] = ArduinoProtocol.NOP;
            buffer[0] <<= ArduinoProtocol.SHIFT_4_LEFT;
            buffer[0] |= ArduinoProtocol.END_PROGRAM;

            return buffer;
        }

        public static byte[] CreateInitExecution()
        {
            byte[] buffer = new byte[1];

            buffer[0] = ArduinoProtocol.NOP;
            buffer[0] <<= ArduinoProtocol.SHIFT_4_LEFT;
            buffer[0] |= ArduinoProtocol.INIT_EXECUTION;

            return buffer;
        }

        public static byte[] CreateFinishExecution()
        {
            byte[] buffer = new byte[1];

            buffer[0] = ArduinoProtocol.NOP;
            buffer[0] <<= ArduinoProtocol.SHIFT_4_LEFT;
            buffer[0] |= ArduinoProtocol.END_PROGRAM;

            return buffer;
        }
    }
}
