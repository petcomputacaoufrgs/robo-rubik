using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using ImageAnalysis;
using RubikCube;

namespace RubikCubeSolver
{
    public static class StoredData
    {
        private static ColorFilterCollection colorFilterCol = new ColorFilterCollection();

        public static Cube Cubo = new Cube();

        #region Filter manipulation methods

        /// <summary>
        /// Adds a filter to the collection
        /// </summary>
        /// <param name="filter">The filter to be added</param>
        public static void AddFilter(ColorFilter filter)
        {
            colorFilterCol.Add(filter);
        }

        /// <summary>
        /// Get the especified filter
        /// </summary>
        /// <param name="filterID">string with the Filter ID</param>
        /// <returns>Return the filter.</returns>
        public static ColorFilter GetFilter(string filterID)
        {
            return colorFilterCol.GetFilter(filterID);
        }

        /// <summary>
        /// Save the filter settings
        /// </summary>
        /// <param name="filename">The file to hold the saved settings</param>
        public static void SaveFilter(string filename)
        {
            colorFilterCol.Save(filename);
        }

        /// <summary>
        /// Load filter settings from XML file.
        /// </summary>
        /// <param name="filename">XML file.</param>
        public static void LoadFiltersFromXml(string filename)
        {
            colorFilterCol.LoadFromXML(filename);
        }

        public static List<ColorFilter> GetAllFilters()
        {
            return colorFilterCol.GetAllFilters();
        }

        #endregion
    }
}
