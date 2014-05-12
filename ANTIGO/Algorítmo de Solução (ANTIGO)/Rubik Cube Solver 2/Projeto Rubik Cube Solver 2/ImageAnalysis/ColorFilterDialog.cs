using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AForge;

namespace ImageAnalysis
{
    /// <summary>
    /// Dialog to adjust ColorFilter object properties
    /// </summary>
    public partial class ColorFilterDialog : Form
    {
        #region Props

        public ColorFilter FilterSettings { get; set; }

        #endregion

        #region Event Handlers

        public delegate void FilterSettingsChangedHandler(object sender, ColorFilterEventArgs e);

        public event FilterSettingsChangedHandler FilterSettingsChanged;

        #endregion

        #region Constructors

        public ColorFilterDialog()
        {
            InitializeComponent();
        }

        #endregion

        #region Methods

        /// <summary>
        /// Set the settings to the FilterSettings propertie
        /// </summary>
        private void SetColorFilter()
        {
            FilterSettings.BorderColor = pnlBorderColor.BackColor;
            FilterSettings.MinWidth = Int32.Parse(numMinWidth.Value.ToString());
            FilterSettings.MinHeight = Int32.Parse(numMinHeight.Value.ToString());
            FilterSettings.Red = new IntRange(trackMinRed.Value, trackMaxRed.Value);
            FilterSettings.Green = new IntRange(trackMinGreen.Value, trackMaxGreen.Value);
            FilterSettings.Blue = new IntRange(trackMinBlue.Value, trackMaxBlue.Value);
        }

        /// <summary>
        /// Initialize control values
        /// </summary>
        private void InitialSettings()
        {
            if (FilterSettings == null)
                FilterSettings = new ColorFilter();

            pnlBorderColor.BackColor = FilterSettings.BorderColor;

            numMinHeight.Value = FilterSettings.MinHeight;
            numMinWidth.Value = FilterSettings.MinWidth;

            trackMinRed.Value = FilterSettings.Red.Min;
            trackMaxRed.Value = FilterSettings.Red.Max;

            trackMinGreen.Value = FilterSettings.Green.Min;
            trackMaxGreen.Value = FilterSettings.Green.Max;

            trackMinBlue.Value = FilterSettings.Blue.Min;
            trackMaxBlue.Value = FilterSettings.Blue.Max;

            txtMinRed.Text = FilterSettings.Red.Min.ToString();
            txtMaxRed.Text = FilterSettings.Red.Max.ToString();

            txtMinGreen.Text = FilterSettings.Green.Min.ToString();
            txtMaxGreen.Text = FilterSettings.Green.Max.ToString();

            txtMinBlue.Text = FilterSettings.Blue.Min.ToString();
            txtMaxBlue.Text = FilterSettings.Blue.Max.ToString();
            SetEventHandlers();
        }

        /// <summary>
        /// Set the event handlers for value change
        /// </summary>
        private void SetEventHandlers()
        {
            EventHandler txtHandler = new EventHandler(this.Textbox_TextChanged);
            EventHandler trackHandler = new EventHandler(this.TrackBarValue_Changed);
            EventHandler numericHandler = new EventHandler(this.NumericUpDown_ValueChanged);
            txtMinRed.TextChanged += txtHandler;
            txtMaxRed.TextChanged += txtHandler;

            txtMinGreen.TextChanged += txtHandler;
            txtMaxGreen.TextChanged += txtHandler;

            txtMinBlue.TextChanged += txtHandler;
            txtMaxBlue.TextChanged += txtHandler;

            trackMinRed.ValueChanged += trackHandler;
            trackMaxRed.ValueChanged += trackHandler;

            trackMinGreen.ValueChanged += trackHandler;
            trackMaxGreen.ValueChanged += trackHandler;

            trackMinBlue.ValueChanged += trackHandler;
            trackMaxBlue.ValueChanged += trackHandler;

            numMinHeight.ValueChanged += numericHandler;
            numMinWidth.ValueChanged += numericHandler;
        }

        #endregion

        #region Events

        private void TrackBarValue_Changed(object sender, EventArgs e)
        {
            TrackBar ctrlSender = (TrackBar)sender;
            string trackName = string.Empty;
            string txtName = ctrlSender.Name.Replace("track", "txt");
            bool isMax = true;
            if (ctrlSender.Name.Contains("Max"))
            {
                trackName = ctrlSender.Name.Replace("Max", "Min");
            }
            else
            {
                trackName = ctrlSender.Name.Replace("Min", "Max");
                isMax = false;
            }
            TrackBar trackFind = null;
            TextBox txtFind = null;
            foreach (Control current in this.Controls)
            {
                if (trackFind == null && current.Name.Equals(trackName))
                {
                    trackFind = (TrackBar)current;
                }
                if (txtFind == null && current.Name.Equals(txtName))
                {
                    txtFind = (TextBox)current;
                }
                if (trackFind != null && txtFind != null) break;
            }
            txtFind.Text = ctrlSender.Value.ToString();
            if (isMax)
            {
                trackFind.Maximum = ctrlSender.Value;
            }
            else
            {
                trackFind.Minimum = ctrlSender.Value;
            }
            SetColorFilter();
            if (FilterSettingsChanged != null)
                this.FilterSettingsChanged(this, new ColorFilterEventArgs() { ChangeType = TypeFilterChanged.RGB });
        }

        private void Textbox_TextChanged(object sender, EventArgs e)
        {
            TextBox txtSender = (TextBox)sender;
            int value;
            bool error = true;
            if (Int32.TryParse(txtSender.Text, out value))
            {
                error = false;
                TrackBar trackWanted = null;
                string nameWanted = txtSender.Name.Replace("txt", "track");
                foreach (Control item in this.Controls)
                {
                    if (item.Name.Equals(nameWanted))
                    {
                        trackWanted = (TrackBar)item;
                        break;
                    }
                }
                if (trackWanted != null)
                {
                    if (trackWanted.Minimum <= value && trackWanted.Maximum >= value)
                        trackWanted.Value = value;
                    else
                        error = true;
                }
            }
            if (error)
            {
                if (txtSender.Text.Length > 0)
                    txtSender.Text = txtSender.Text.Substring(0, txtSender.Text.Length - 1);
                else
                    txtSender.Text = "0";
                txtSender.Select(txtSender.Text.Length, 1);
            }
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ColorFilterDialog_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible)
            {
                InitialSettings();

                trackMinRed.Maximum = trackMaxRed.Value;
                trackMaxRed.Minimum = trackMinRed.Value;

                trackMinGreen.Maximum = trackMaxGreen.Value;
                trackMaxGreen.Minimum = trackMinGreen.Value;

                trackMinBlue.Maximum = trackMaxBlue.Value;
                trackMaxBlue.Minimum = trackMinBlue.Value;
            }
        }

        private void NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            SetColorFilter();
            if (FilterSettingsChanged != null)
                this.FilterSettingsChanged(this, new ColorFilterEventArgs() { ChangeType = TypeFilterChanged.RectangleSize });
        }

        #endregion
    }
}
