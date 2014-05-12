using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;

namespace ImageAnalysis
{
    /// <summary>
    /// Collection of ColorFilter objects
    /// </summary>
    public class ColorFilterCollection : System.Collections.CollectionBase
    {
        #region Private Methods

        /// <summary>
        /// Translate a ColorFilter objet to XML.
        /// </summary>
        /// <param name="filter">ColorFilter to translate</param>
        /// <param name="xmlDoc">XmlDocument to append</param>
        /// <returns>Return the XmlElement with the ColorFilter translated</returns>
        private XmlElement TranslateToXML(ColorFilter filter, XmlDocument xmlDoc)
        {
            XmlElement element = xmlDoc.CreateElement("filter");
            element.SetAttribute("filterID", filter.FilterID);
            element.SetAttribute("minWidth", filter.MinWidth.ToString());
            element.SetAttribute("minHeight", filter.MinHeight.ToString());
            element.SetAttribute("borderColor", filter.BorderColor.ToArgb().ToString());

            XmlElement redEl = xmlDoc.CreateElement("red");
            redEl.SetAttribute("min", filter.Red.Min.ToString());
            redEl.SetAttribute("max", filter.Red.Max.ToString());

            XmlElement greenEl = xmlDoc.CreateElement("green");
            greenEl.SetAttribute("min", filter.Green.Min.ToString());
            greenEl.SetAttribute("max", filter.Green.Max.ToString());

            XmlElement blueEl = xmlDoc.CreateElement("blue");
            blueEl.SetAttribute("min", filter.Blue.Min.ToString());
            blueEl.SetAttribute("max", filter.Blue.Max.ToString());

            element.AppendChild(redEl);
            element.AppendChild(greenEl);
            element.AppendChild(blueEl);
            return element;
        }

        /// <summary>
        /// Translate a XmlNode into a ColorFilter object.
        /// </summary>
        /// <param name="element">XmlNode with the ColorFilter</param>
        /// <returns>Return the ColorFilter.</returns>
        private ColorFilter TranslateFromXML(XmlNode element)
        {
            ColorFilter filter = new ColorFilter();
            filter.FilterID = element.Attributes["filterID"].Value;
            filter.MinWidth = Int16.Parse(element.Attributes["minWidth"].Value);
            filter.MinHeight = Int16.Parse(element.Attributes["minHeight"].Value);
            filter.BorderColor = System.Drawing.Color.FromArgb(Int32.Parse(element.Attributes["borderColor"].Value));
            XmlNode redNode = element.ChildNodes[0];
            XmlNode greenNode = element.ChildNodes[1];
            XmlNode blueNode = element.ChildNodes[2];

            filter.Red.Min = Int32.Parse(redNode.Attributes["min"].Value);
            filter.Red.Max = Int32.Parse(redNode.Attributes["max"].Value);

            filter.Green.Min = Int32.Parse(greenNode.Attributes["min"].Value);
            filter.Green.Max = Int32.Parse(greenNode.Attributes["max"].Value);

            filter.Blue.Min = Int32.Parse(blueNode.Attributes["min"].Value);
            filter.Blue.Max = Int32.Parse(blueNode.Attributes["max"].Value);
            return filter;
        }

        #endregion

        #region Public methods

        /// <summary>
        /// Add a new ColorFilter object
        /// </summary>
        /// <param name="filter"></param>
        public void Add(ColorFilter filter)
        {
            try
            {
                int index = this.GetFilterIndex(filter.FilterID);
                List[index] = filter;
            }
            catch
            {
                List.Add(filter);
            }
        }

        /// <summary>
        /// Get the especific ColorFilter
        /// </summary>
        /// <param name="FilterID">string with the filter ID</param>
        /// <returns>Return, if found, the ColorFilter.</returns>
        public ColorFilter GetFilter(string FilterID)
        {
            ColorFilter filter = new ColorFilter();
            bool found = false;
            int i = 0;
            if (List.Count > 0)
            {
                while (!found && i < List.Count)
                {
                    filter = (ColorFilter)List[i];
                    found = filter.FilterID.Equals(FilterID);
                    i++;
                }
            }
            if (!found)
                throw new InvalidOperationException("ColorFilter not found");
            return filter;
        }

        /// <summary>
        /// Get the index of the especific ColorFilter
        /// </summary>
        /// <param name="FilterID">string with the filter ID</param>
        /// <returns>Return, if found, the index.</returns>
        public int GetFilterIndex(string FilterID)
        {
            ColorFilter filter;
            bool found = false;
            int i = 0;
            if (List.Count > 0)
            {
                while (!found && i < List.Count)
                {
                    filter = (ColorFilter)List[i];
                    found = filter.FilterID.Equals(FilterID);
                    i++;
                }
            }
            if (!found)
                throw new InvalidOperationException("ColorFilter not found");
            return i - 1;
        }

        /// <summary>
        /// Save the settings into a xml file
        /// </summary>
        /// <param name="filename">String with the file path.</param>
        public void Save(string filename)
        {
            XmlDocument xDoc = new XmlDocument();
            XmlDeclaration dec = xDoc.CreateXmlDeclaration("1.0", null, null);
            xDoc.AppendChild(dec);
            XmlElement root = xDoc.CreateElement("Settings");
            for (int i = 0; i < List.Count; i++)
            {
                XmlElement elem = TranslateToXML((ColorFilter)List[i], xDoc);
                root.AppendChild(elem);
            }
            xDoc.AppendChild(root);
            xDoc.Save(filename);
        }

        /// <summary>
        /// Load Collection from XML file.
        /// </summary>
        /// <param name="filename">String with the XML filename.</param>
        public void LoadFromXML(string filename)
        {
            XmlDocument xDoc = new XmlDocument();
            xDoc.Load(filename);
            XmlNode root = xDoc.ChildNodes[1];
            foreach (XmlNode item in root.ChildNodes)
            {
                ColorFilter filter = TranslateFromXML(item);
                this.Add(filter);
            }
        }

        public List<ColorFilter> GetAllFilters()
        {
            List<ColorFilter> filters = new List<ColorFilter>();
            int i = 0;
            if (List.Count > 0)
            {
                while (i < List.Count)
                {
                    filters.Add((ColorFilter)List[i]);
                    i++;
                }
            }
            return filters;
        }

        #endregion
    }
}
