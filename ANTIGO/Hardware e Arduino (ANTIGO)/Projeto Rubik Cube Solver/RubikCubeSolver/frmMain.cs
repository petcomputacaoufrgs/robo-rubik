using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ImageAnalysis;
using AForge;
using System.Collections;
using System.IO;
using System.Xml.Serialization;
using RubikCube;
using System.Diagnostics;
using System.Runtime.InteropServices;
using CubeSolver;
using ArduinoCommunication;

namespace RubikCubeSolver
{
    public partial class frmMain : Form
    {
        #region Fields

        private ColorFilterDialog clFilterDiag = new ColorFilterDialog();

        private VisualCubeFace face = new VisualCubeFace();

        private VisualCube cube = new VisualCube();

        private bool lockImage = false;

        #endregion

        #region Props

        /// <summary>
        /// Face found in the image source
        /// </summary>
        public VisualCubeFace CurrentFace
        {
            get { return this.face; }
            set { this.face = value; }
        }

        /// <summary>
        /// The current cube
        /// </summary>
        public VisualCube CurrentCube
        {
            get { return this.cube; }
            set { this.cube = value; }
        }

        /// <summary>
        /// Locks the stored image
        /// </summary>
        public bool LockImage
        {
            get { return this.lockImage; }
            set { this.lockImage = value; }
        }

        #endregion

        #region Constructors

        public frmMain()
        {
            InitializeComponent();
        }

        #endregion

        #region Methods

        /// <summary>
        /// Get the parent block of a given region
        /// </summary>
        /// <param name="blocks">List of blocks in the image</param>
        /// <param name="current">Current region</param>
        /// <param name="selected">The parent block</param>
        /// <returns>Returns true if the region is inside some block.</returns>
        private bool HasParentBlock(List<Rectangle> blocks, Rectangle current, out Rectangle selected)
        {
            selected = new Rectangle();
            bool worked = false;
            foreach (Rectangle item in blocks)
            {
                if (item.Contains(current) || item.Equals(current) || current.Contains(item))
                {
                    selected = item;
                    worked = true;
                    break;
                }
            }
            return worked;
        }

        /// <summary>
        /// Find all objects in image.
        /// </summary>
        private void FindObjectsOfAllImages()
        {
            if (CubeAnalyser.SourceImage != null)
            {
                this.CurrentFace.ClearBlocks();
                ImageAnalyser analyser = new ImageAnalyser();
                picbVideoCapture.Image = (Image)CubeAnalyser.SourceImage.Clone();
                Graphics g = Graphics.FromImage(picbVideoCapture.Image);
                List<Rectangle> blocks = analyser.GetSquares(CubeAnalyser.SourceImage, (int)numMinWidth.Value, (int)numMinHeight.Value);
                //Color1
                FindObjectsOfImage(picbRedFilter.Image, StoredData.GetFilter(picbRedFilter.Name), blocks, g, analyser);
                //Color2
                FindObjectsOfImage(picbBlueFilter.Image, StoredData.GetFilter(picbBlueFilter.Name), blocks, g, analyser);
                //Color3
                FindObjectsOfImage(picbGreenFilter.Image, StoredData.GetFilter(picbGreenFilter.Name), blocks, g, analyser);
                //Color4
                FindObjectsOfImage(picbYellowFilter.Image, StoredData.GetFilter(picbYellowFilter.Name), blocks, g, analyser);
                //Color5
                FindObjectsOfImage(picbOrangeFilter.Image, StoredData.GetFilter(picbOrangeFilter.Name), blocks, g, analyser);
                //Color6
                FindObjectsOfImage(picbWhiteFilter.Image, StoredData.GetFilter(picbWhiteFilter.Name), blocks, g, analyser);
            }
        }

        /// <summary>
        /// Find the objects in the image.
        /// </summary>
        /// <param name="image">The image to search for objects</param>
        /// <param name="filter">The filter with color</param>
        /// <param name="g">The Graphics to draw the rectangles</param>
        /// <param name="analyser">The ImageAnalyser to analysis the image</param>
        private void FindObjectsOfImage(Image image, ColorFilter filter, List<Rectangle> blocksFace, Graphics g, ImageAnalyser analyser)
        {
            Pen p = new Pen(filter.BorderColor, 3.0F);
            foreach (Rectangle item in analyser.GetObjectsCoordinates(image, filter))
            {
                VisualCubeBlock newFacelet = new VisualCubeBlock();
                newFacelet.Color = ColorTranslate.getFaceColorByColor(p.Color);
                Rectangle coord = new Rectangle();
                if (HasParentBlock(blocksFace, item, out coord))
                {
                    newFacelet.Rectangle = coord;
                    this.CurrentFace.AddBlock(newFacelet.Clone(), true);
                    g.DrawRectangle(p, coord);
                }
                newFacelet.Dispose();
            }
        }

        /// <summary>
        /// Finds the objects of the image
        /// </summary>
        /// <param name="image">The image to look for objects</param>
        /// <param name="filter">The filter with the minHeight and minWidth</param>
        private void FindObjectsOfImage(Image image, ColorFilter filter)
        {
            ImageAnalyser analyser = new ImageAnalyser();
            Graphics g = Graphics.FromImage(picbVideoCapture.Image);
            List<Rectangle> blocks = analyser.GetSquares(CubeAnalyser.SourceImage, (int)numMinWidth.Value, (int)numMinHeight.Value);
            FindObjectsOfImage(image, filter, blocks, g, analyser);
        }

        /// <summary>
        /// Find the objects in the image
        /// </summary>
        /// <param name="picBox">`Picture box with the image</param>
        private void FindObjectsOfImage(PictureBox picBox)
        {
            FindObjectsOfImage(picBox.Image, StoredData.GetFilter(picBox.Name));
        }

        /// <summary>
        /// Filter all images
        /// </summary>
        private void FilterAllImages()
        {
            if (picbVideoCapture.Image != null)
            {
                ImageAnalyser analyser = new ImageAnalyser();
                //Color 1;
                picbRedFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbRedFilter.Name), CubeAnalyser.SourceImage);
                //Color 2;
                picbBlueFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbBlueFilter.Name), CubeAnalyser.SourceImage);
                //Color 3;
                picbGreenFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbGreenFilter.Name), CubeAnalyser.SourceImage);
                //Color 4;
                picbYellowFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbYellowFilter.Name), CubeAnalyser.SourceImage);
                //Color 5;
                picbOrangeFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbOrangeFilter.Name), CubeAnalyser.SourceImage);
                //Color 6;
                picbWhiteFilter.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picbWhiteFilter.Name), CubeAnalyser.SourceImage);
                FindObjectsOfAllImages();
            }
        }

        /// <summary>
        /// Filter especific image.
        /// </summary>
        /// <param name="picBox">Picturebox to show the filtered image</param>
        private void FilterImage(PictureBox picBox)
        {
            if (picbVideoCapture.Image != null)
            {
                ImageAnalyser analyser = new ImageAnalyser();
                picBox.Image = analyser.ApplyColorFilter(StoredData.GetFilter(picBox.Name), CubeAnalyser.SourceImage);
            }
        }

        /// <summary>
        /// Links the radiobutton objects to the respective picturebox
        /// </summary>
        private void LinkRadioToPicture()
        {
            //Link between radiobuttons and picturebox
            radColor1.Tag = picbRedFilter;
            radColor2.Tag = picbBlueFilter;
            radColor3.Tag = picbGreenFilter;
            radColor4.Tag = picbYellowFilter;
            radColor5.Tag = picbOrangeFilter;
            radColor6.Tag = picbWhiteFilter;
        }

        /// <summary>
        /// Links the picturebox objects to the respectives color filters
        /// </summary>
        private void LinkPictureToFilter()
        {
            foreach (Control item in groupImgProc.Controls)
            {
                if (item is PictureBox)
                {
                    ColorFilter newFilter = new ColorFilter();
                    newFilter.FilterID = item.Name;
                    if (item.Name.Contains("Red"))
                        newFilter.BorderColor = Color.Red;
                    else if (item.Name.Contains("Blue"))
                        newFilter.BorderColor = Color.Blue;
                    else if (item.Name.Contains("Green"))
                        newFilter.BorderColor = Color.Green;
                    else if (item.Name.Contains("Yellow"))
                        newFilter.BorderColor = Color.Yellow;
                    else if (item.Name.Contains("Orange"))
                        newFilter.BorderColor = Color.Orange;
                    else
                        newFilter.BorderColor = Color.White;
                    StoredData.AddFilter(newFilter);
                }
            }
        }

        /// <summary>
        /// Save the filter settings.
        /// </summary>
        private void SaveFilterSettings()
        {
            SaveFileDialog diag = new SaveFileDialog();
            diag.Filter = "Settings save file | *.sav";
            if (diag.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                StoredData.SaveFilter(diag.FileName);
        }

        /// <summary>
        /// Load filter settings from XML.
        /// </summary>
        private void LoadFilterSettings()
        {
            OpenFileDialog diag = new OpenFileDialog();
            diag.Filter = "Settings save file|*.sav";
            if (diag.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                StoredData.LoadFiltersFromXml(diag.FileName);
        }

        /// <summary>
        /// Gets the selected radiobutton of the ImageProcessing GroupBox
        /// </summary>
        /// <returns>Returns the control</returns>
        private Control GetSelectedRadioButton()
        {
            Control ctrl = new Control();
            foreach (Control item in groupImgProc.Controls)
            {
                if (item is RadioButton && ((RadioButton)item).Checked)
                {
                    ctrl = item;
                    break;
                }
            }
            return ctrl;
        }

        /// <summary>
        /// Apply the filters configured in the Filter Settings Dialog
        /// </summary>
        private void ApplyFilterChanges()
        {
            Control radioBtn = GetSelectedRadioButton();
            Control pic = (Control)radioBtn.Tag;
            clFilterDiag.FilterSettings.FilterID = pic.Name;
            StoredData.AddFilter(clFilterDiag.FilterSettings);
        }

        /// <summary>
        /// Gets the the filter related to the selected radiobutton
        /// </summary>
        /// <returns>Returns the colorfilter.</returns>
        private ColorFilter GetCurrentFilter()
        {
            Control radioBtn = GetSelectedRadioButton();
            Control pic = (Control)radioBtn.Tag;
            return StoredData.GetFilter(pic.Name);
        }

        /// <summary>
        /// Configure the ColorFilterDialog
        /// </summary>
        private void SetColorFilterDialog()
        {
            clFilterDiag = new ColorFilterDialog();
            clFilterDiag.FilterSettings = GetCurrentFilter();
            clFilterDiag.FilterSettingsChanged += new ColorFilterDialog.FilterSettingsChangedHandler(ColorFilterDialog_FilterSettingsChanged);
        }

        #endregion

        #region Events

        private void btnStartCam_EnabledChanged(object sender, EventArgs e)
        {
            btnStopCam.Enabled = !btnStartCam.Enabled;
            btnVideoFormat.Enabled = btnStopCam.Enabled;
        }

        private void btnStartCam_Click(object sender, EventArgs e)
        {
            btnStartCam.Enabled = false;
            videoCaptureDevice1.Start();
        }

        private void btnStopCam_Click(object sender, EventArgs e)
        {
            btnStartCam.Enabled = true;
            videoCaptureDevice1.Stop();
        }

        private void videoCaptureDevice1_ImageCaptured(object source, VideoCapture.ImageCapturedEventArgs e)
        {
            // set the picturebox picture
            CubeAnalyser.SourceImage = e.WebCamImage;
            saveImageToolStripMenuItem.Enabled = true;
            this.picbVideoCapture.Image = (Image)e.WebCamImage.Clone();
            this.picbFaceImg.Image = (Image)e.WebCamImage.Clone();
            FilterAllImages();
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (btnStopCam.Enabled)
                videoCaptureDevice1.Stop();
            if (!clFilterDiag.IsDisposed)
            {
                clFilterDiag.Close();
            }
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            LinkRadioToPicture();
            LinkPictureToFilter();
            cboFaceTypes.DataSource = Enum.GetValues(typeof(CubeFaceType));
            cboFaceToTurn.DataSource = Enum.GetValues(typeof(CubeFaceType));
        }

        private void ColorFilterDialog_FilterSettingsChanged(object sender, ColorFilterEventArgs e)
        {
            ApplyFilterChanges();
            switch (e.ChangeType)
            {
                case TypeFilterChanged.RGB:
                    if (btnStartCam.Enabled)
                    {
                        Control radio = GetSelectedRadioButton();
                        FilterImage((PictureBox)radio.Tag);
                    }
                    break;
                case TypeFilterChanged.RectangleSize:
                    if (btnStartCam.Enabled)
                    {
                        Control radio = GetSelectedRadioButton();
                        picbVideoCapture.Image = (Image)CubeAnalyser.SourceImage.Clone();
                        FindObjectsOfImage((PictureBox)radio.Tag);
                    }
                    break;
                default:
                    break;
            }
        }

        private void btnConfigColorFilter_Click(object sender, EventArgs e)
        {
            SetColorFilterDialog();
            clFilterDiag.Show(this);
        }

        private void btnLoadImage_Click(object sender, EventArgs e)
        {
            OpenFileDialog diag = new OpenFileDialog();
            diag.Filter = "Image Files|*.BMP;*.JPG;*.GIF;*.PNG";
            if (diag.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                saveImageToolStripMenuItem.Enabled = true;
                CubeAnalyser.SourceImage = Image.FromFile(diag.FileName);
                picbVideoCapture.Image = (Image)CubeAnalyser.SourceImage.Clone();
                picbFaceImg.Image = (Image)CubeAnalyser.SourceImage.Clone();
                FilterAllImages();
            }
        }

        private void btnSaveSettings_Click(object sender, EventArgs e)
        {
            SaveFilterSettings();
        }

        private void btnLoadSettings_Click(object sender, EventArgs e)
        {
            LoadFilterSettings();
            if (btnStartCam.Enabled)
            {
                FilterAllImages();
                picbFaceImg.Invalidate();
            }
        }

        private void saveImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog diag = new SaveFileDialog();
            diag.Filter = "Image Files|*.BMP;*.JPG;*.GIF;*.PNG";
            if (diag.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                CubeAnalyser.SourceImage.Save(diag.FileName);
        }

        private void videoFormatToolStripMenuItem_Click(object sender, EventArgs e)
        {
            videoCaptureDevice1.ShowVideoFormatDialog();
        }

        private void picbFaceImg_Paint(object sender, PaintEventArgs e)
        {
            lblFaceletsCount.Text = this.CurrentFace.GetBlocksCount().ToString();
        }

        private void btnSetFace_Click(object sender, EventArgs e)
        {
            this.LockImage = true;
            this.CurrentFace.SortBlockList();
            this.LockImage = false;

            this.CurrentFace.FaceType = (CubeFaceType)cboFaceTypes.SelectedIndex;
            this.CurrentCube.AddFace(this.CurrentFace);
            picbCubeDiagram.Invalidate();

        }

        private void btnFilterImage_Click(object sender, EventArgs e)
        {
            FilterAllImages();
        }

        private void lblFaceletsCount_TextChanged(object sender, EventArgs e)
        {
            int val;
            if (Int32.TryParse(lblFaceletsCount.Text, out val))
            {
                btnSetFace.Enabled = (val == 9);
            }
        }

        private void btnClearDiagram_Click(object sender, EventArgs e)
        {
            this.CurrentCube.ClearAllFaces();
            picbCubeDiagram.Refresh();
        }

        private void picbCubeDiagram_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            foreach (VisualCubeFace face in this.CurrentCube.GetFaces())
            {
                foreach (VisualCubeBlock item in face.GetBlocks())
                {
                    Rectangle rec = new Rectangle(CubeDiagramFiller.GetPoint(face.FaceType, item.Square), new Size(18, 18));
                    SolidBrush br = new SolidBrush(ColorTranslate.getColorByEnumValue(item.Color));
                    g.FillRectangle(br, rec);
                }
            }

        }

        private void btnMoveCube_Click(object sender, EventArgs e)
        {
            Coordinate coord = new Coordinate((CoordinateAxis)cboAxisType.SelectedIndex, Int32.Parse(cboAxisValue.SelectedItem.ToString()));
            if (chkIsToFace.Checked)
            {
                this.CurrentCube.TurnFace((CubeFaceType)cboFaceToTurn.SelectedIndex, coord);
            }
            else
            {
                this.CurrentCube.TurnCube(coord);
            }
            picbCubeDiagram.Invalidate();
        }

        private void SquareDimensions_Change(object sender, EventArgs e)
        {
            FindObjectsOfAllImages();
        }

        private void btnBuildDefaultCube_Click(object sender, EventArgs e)
        {
            Array facesArray = Enum.GetValues(typeof(CubeFaceType));
            Array squaresArray = Enum.GetValues(typeof(CubeFaceletType));
            CubeFaceColor[] colors = new CubeFaceColor[] { CubeFaceColor.R, CubeFaceColor.O, CubeFaceColor.B, CubeFaceColor.G, CubeFaceColor.W, CubeFaceColor.Y };
            for (int i = 0; i < facesArray.Length; i++)
            {
                VisualCubeFace face = new VisualCubeFace();
                face.FaceType = (CubeFaceType)facesArray.GetValue(i);
                foreach (CubeFaceletType item in squaresArray)
                {
                    VisualCubeBlock block = new VisualCubeBlock();
                    block.Square = item;
                    block.Color = colors[i];
                    face.AddBlock(block.Clone(), false);
                    block.Dispose();
                }
                this.CurrentCube.AddFace(face.Clone());
                face.Dispose();
            }
            picbCubeDiagram.Invalidate();
        }

        #endregion

        [DllImport("KociembaRubikSolver.dll", EntryPoint = "SolveRubikCube")]
        public static extern unsafe IntPtr SolveRubikCube(void* cubeAsString);

        public static unsafe string SolveRubikCube(string cubeAsString)
        {
            IntPtr filePtr = IntPtr.Zero;
            try
            {
                filePtr = Marshal.StringToHGlobalAnsi(cubeAsString);
                IntPtr t = SolveRubikCube(filePtr.ToPointer());
                return Marshal.PtrToStringAnsi(t); ;
            }
            finally
            {
                if (filePtr != IntPtr.Zero)
                    Marshal.FreeHGlobal(filePtr);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.CurrentCube.TurnFace(CubeFaceType.U, new Coordinate(CoordinateAxis.Z, -90));
            this.picbCubeDiagram.Invalidate();
        }

        private void chkIsToFace_CheckedChanged(object sender, EventArgs e)
        {
            cboFaceToTurn.Enabled = chkIsToFace.Checked;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            RobotCubeSolver solver = new RobotCubeSolver(new Cube());
            List<Movement> movements = solver.Solve(textBox1.Text);
            movimentosText.Text = "";
            foreach (Movement movement in movements)
            {
                movimentosText.Text += movement.toString() + "\n";
            }
            movementsProtocol.Text = ArduinoProtocol.CreateBitRepresentationOfMovements(movements);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // aqui entra o programa principal

            StoredData.Cubo = CubeAnalyser.AnalyseCube(StoredData.GetAllFilters(), 10, 10, null);
        }
    }
}
