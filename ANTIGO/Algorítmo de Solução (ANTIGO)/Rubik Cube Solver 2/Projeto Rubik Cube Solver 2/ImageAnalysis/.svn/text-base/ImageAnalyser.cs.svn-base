using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using AForge.Imaging.Filters;
using AForge.Math.Geometry;
using AForge.Imaging;
using AForge;


namespace ImageAnalysis
{
    /// <summary>
    /// Class that analyse images
    /// </summary>
    public class ImageAnalyser
    {
        private List<Rectangle> Squares = new List<Rectangle>();

        private Dictionary<Rectangle, Color> facelets = new Dictionary<Rectangle, Color>();

        public List<ColorFilter> Filters { get; set; }

        public ImageSample Sample { get; set; }

        public void AnalyseImageSample(Object threadContext)
        {
            List<Rectangle> mainSquares = GetSquares(this.Sample.Sample, this.Sample.FaceletMinWidth, this.Sample.FaceletMinHeight);
            this.Sample.Facelets.Clear();
            foreach (ColorFilter filter in Filters)
            {
                Bitmap smp = ApplyColorFilter(filter, this.Sample.Sample);
                FindObjectsOfImage((System.Drawing.Image)smp, filter, ref this.Sample.Facelets);
            }
            /*
            GetSquares
            Loops all the filters
                ApplyColorFilter
                FindObjectsOfImage
                Add them to sample
            */
        }


        /// <summary>
        /// Apply color filter in image.
        /// </summary>
        /// <param name="filter">ColorFilter object with the RGB weightining</param>
        /// <param name="img">Image to filter</param>
        /// <returns>Return a Bitmap object with the image filtered</returns>
        public Bitmap ApplyColorFilter(ColorFilter filter, System.Drawing.Image img)
        {
            Bitmap filteredImg = new Bitmap((System.Drawing.Image)img.Clone());
            filter.ApplyInPlace(filteredImg);
            return filteredImg;
        }

        /// <summary>
        /// Get rectangles objects in the image
        /// </summary>
        /// <param name="image">Image to get the rectangles</param>
        /// <param name="filter">ColorFilter with the minimum height and minimum width</param>
        /// <returns>Return a rectangle array with the object coordinates</returns>
        public Rectangle[] GetObjectsCoordinates(System.Drawing.Image image, ColorFilter filter)
        {
            return GetObjectsCoordinates(image, filter.MinWidth, filter.MinHeight);
        }

        /// <summary>
        /// Get rectangles objects in the image
        /// </summary>
        /// <param name="image">Image to get the rectangles</param>
        /// <param name="minWidth">Minimum width to consider as a valid rectangle</param>
        /// <param name="minHeight">Minimum height to consider as a valid ractangle</param>
        /// <returns>Return an array with the selected rectangle</returns>
        public Rectangle[] GetObjectsCoordinates(System.Drawing.Image image, int minWidth, int minHeight)
        {
            // create grayscale filter
            GrayscaleBT709 grayscaleFilter = new GrayscaleBT709();
            // apply it to color filtered image
            Bitmap grayImage = grayscaleFilter.Apply(new Bitmap(image));

            // create blob counter
            AForge.Imaging.BlobCounter blobCounter = new AForge.Imaging.BlobCounter();
            // configure it to filter out small objects
            blobCounter.MinWidth = minWidth;
            blobCounter.MinHeight = minHeight;
            blobCounter.FilterBlobs = true;
            // set ordering - bigger objects go first
            blobCounter.ObjectsOrder = AForge.Imaging.ObjectsOrder.YX;

            // locate blobs
            blobCounter.ProcessImage(grayImage);
            Rectangle[] rects = blobCounter.GetObjectsRectangles();
            return rects;
        }

        /// <summary>
        /// Gets the squares in the image
        /// </summary>
        /// <param name="cubeFace">Image to get the squares</param>
        /// <param name="minWidth">Minimum square width</param>
        /// <param name="minHeight">Minimum square height</param>
        /// <returns>Returns the list with the squares.</returns>
        public List<Rectangle> GetSquares(System.Drawing.Image cubeFace, int minWidth, int minHeight)
        {
            Squares = new List<Rectangle>();
            Bitmap bitmap = new Bitmap(cubeFace);
            // lock image
            System.Drawing.Imaging.BitmapData bitmapData = bitmap.LockBits(
                new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                System.Drawing.Imaging.ImageLockMode.ReadWrite, bitmap.PixelFormat);

            // step 1 - turn background to black
            ColorFiltering colorFilter = new ColorFiltering();

            colorFilter.Red = new AForge.IntRange(0, 64);
            colorFilter.Green = new AForge.IntRange(0, 64);
            colorFilter.Blue = new AForge.IntRange(0, 64);
            colorFilter.FillOutsideRange = false;

            colorFilter.ApplyInPlace(bitmapData);

            // step 2 - locating objects
            BlobCounter blobCounter = new BlobCounter();

            blobCounter.FilterBlobs = true;
            blobCounter.MinHeight = minHeight;
            blobCounter.MinWidth = minWidth;

            blobCounter.ProcessImage(bitmapData);
            AForge.Imaging.Blob[] blobs = blobCounter.GetObjectsInformation();
            bitmap.UnlockBits(bitmapData);

            // step 3 - check objects' type and highlight
            SimpleShapeChecker shapeChecker = new SimpleShapeChecker();
            for (int i = 0, n = blobs.Length; i < n; i++)
            {
                List<IntPoint> edgePoints = blobCounter.GetBlobsEdgePoints(blobs[i]);
                List<IntPoint> corners;
                // is triangle or quadrilateral
                if (shapeChecker.IsConvexPolygon(edgePoints, out corners) && corners.Count == 4)
                {
                    Squares.Add(blobs[i].Rectangle);
                }
            }
            return Squares;
        }

        /// <summary>
        /// Find the objects in the image.
        /// </summary>
        /// <param name="image">The image to search for objects</param>
        /// <param name="filter">The filter with color</param>
        public void FindObjectsOfImage(System.Drawing.Image image, ColorFilter filter)
        {
            foreach (Rectangle item in this.GetObjectsCoordinates(image, filter))
            {
                Rectangle coord = new Rectangle();
                if (HasParentBlock(Squares, item, out coord))
                {
                    facelets.Add(coord, filter.BorderColor);
                }
            }
        }

        public void FindObjectsOfImage(System.Drawing.Image image, ColorFilter filter, ref Dictionary<Rectangle, Color> dictio)
        {
            foreach (Rectangle item in this.GetObjectsCoordinates(image, filter))
            {
                Rectangle coord = new Rectangle();
                if (HasParentBlock(Squares, item, out coord))
                {
                    dictio.Add(coord, filter.BorderColor);
                }
            }
        }

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
    }
}
