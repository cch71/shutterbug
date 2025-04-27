using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Net;
using System.IO;
using System.Text;
using CraigsCreations.com.WebCamera;

namespace ShutterBugNetTest
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmMain : System.Windows.Forms.Form
	{
		private System.Windows.Forms.PictureBox previewVideo;
		private System.Windows.Forms.Button btnRun;
		private System.Windows.Forms.Button btnSnapPicture;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnPostPicture;
		private System.Windows.Forms.Button btnBringItAllTogether;
		private System.Windows.Forms.Label lblCaption;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public frmMain()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.previewVideo = new System.Windows.Forms.PictureBox();
			this.btnRun = new System.Windows.Forms.Button();
			this.btnSnapPicture = new System.Windows.Forms.Button();
			this.btnStop = new System.Windows.Forms.Button();
			this.btnPostPicture = new System.Windows.Forms.Button();
			this.btnBringItAllTogether = new System.Windows.Forms.Button();
			this.lblCaption = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// previewVideo
			// 
			this.previewVideo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.previewVideo.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.previewVideo.Location = new System.Drawing.Point(0, 30);
			this.previewVideo.Name = "previewVideo";
			this.previewVideo.Size = new System.Drawing.Size(544, 288);
			this.previewVideo.TabIndex = 0;
			this.previewVideo.TabStop = false;
			// 
			// btnRun
			// 
			this.btnRun.Location = new System.Drawing.Point(8, 0);
			this.btnRun.Name = "btnRun";
			this.btnRun.TabIndex = 1;
			this.btnRun.Text = "Run";
			this.btnRun.Click += new System.EventHandler(this.btnRun_Click);
			// 
			// btnSnapPicture
			// 
			this.btnSnapPicture.Location = new System.Drawing.Point(104, 0);
			this.btnSnapPicture.Name = "btnSnapPicture";
			this.btnSnapPicture.TabIndex = 1;
			this.btnSnapPicture.Text = "Snap Photo";
			this.btnSnapPicture.Click += new System.EventHandler(this.btnSnapPicture_Click);
			// 
			// btnStop
			// 
			this.btnStop.Location = new System.Drawing.Point(192, 0);
			this.btnStop.Name = "btnStop";
			this.btnStop.TabIndex = 1;
			this.btnStop.Text = "Stop";
			this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
			// 
			// btnPostPicture
			// 
			this.btnPostPicture.Location = new System.Drawing.Point(280, 0);
			this.btnPostPicture.Name = "btnPostPicture";
			this.btnPostPicture.TabIndex = 1;
			this.btnPostPicture.Text = "Post Picture";
			this.btnPostPicture.Click += new System.EventHandler(this.btnPostPicture_Click);
			// 
			// btnBringItAllTogether
			// 
			this.btnBringItAllTogether.Location = new System.Drawing.Point(368, 0);
			this.btnBringItAllTogether.Name = "btnBringItAllTogether";
			this.btnBringItAllTogether.Size = new System.Drawing.Size(120, 23);
			this.btnBringItAllTogether.TabIndex = 1;
			this.btnBringItAllTogether.Text = "Bring It All Together";
			this.btnBringItAllTogether.Click += new System.EventHandler(this.btnBringItAllTogether_Click);
			// 
			// lblCaption
			// 
			this.lblCaption.BackColor = System.Drawing.Color.Transparent;
			this.lblCaption.Font = new System.Drawing.Font("Arial", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.lblCaption.ForeColor = System.Drawing.SystemColors.ControlText;
			this.lblCaption.Location = new System.Drawing.Point(168, 288);
			this.lblCaption.Name = "lblCaption";
			this.lblCaption.Size = new System.Drawing.Size(176, 23);
			this.lblCaption.TabIndex = 2;
			this.lblCaption.Text = "Caption";
			this.lblCaption.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// frmMain
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(544, 318);
			this.Controls.Add(this.lblCaption);
			this.Controls.Add(this.btnRun);
			this.Controls.Add(this.previewVideo);
			this.Controls.Add(this.btnSnapPicture);
			this.Controls.Add(this.btnStop);
			this.Controls.Add(this.btnPostPicture);
			this.Controls.Add(this.btnBringItAllTogether);
			this.Name = "frmMain";
			this.Text = "Video Camera Test";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.OnClosing);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmMain());
		}

		private void btnRun_Click(object sender, System.EventArgs e)
		{
			CameraController.Start(previewVideo.Handle,previewVideo.DisplayRectangle);
		}

		private void btnSnapPicture_Click(object sender, System.EventArgs e)
		{
//			CameraController.SnapPhotoToFile(@"c:\dotnetimage.bmp");
			byte[] imageArray = CameraController.SnapPhoto();
			if(null==imageArray) { return; }
			MemoryStream imageStream = new MemoryStream(imageArray);
			Bitmap bmpImg = new Bitmap(imageStream);
			bmpImg.Save(@"C:\dotinetimage.bmp");
//			CameraController.TimedPhotoEvent +=new TimedPhotoEventHandler(this.OnTimedPhoto);
//			CameraController.SnapTimedPhoto(10000/*1000 60 * 15*/,true);		

		}

		private void btnStop_Click(object sender, System.EventArgs e)
		{
			CameraController.Stop();
			btnBringItAllTogether.Enabled = true;

		}

		private void OnTimedPhoto(Bitmap image)
		{
//			string fileName = @"c:\debugimg.jpg";
//			image.Save(fileName,System.Drawing.Imaging.ImageFormat.Jpeg);
			PostPicture(image);
			System.Diagnostics.Trace.WriteLine("Picture Taken: " + System.DateTime.Now);
		}
		
		private void PostPicture(Bitmap image) 
		{
			ASCIIEncoding encoder = new ASCIIEncoding();
			MemoryStream streamImage = new MemoryStream();
			image.Save(streamImage,System.Drawing.Imaging.ImageFormat.Jpeg);
			byte[] byteImageArray = streamImage.GetBuffer();
			string encodedImageString = Convert.ToBase64String(byteImageArray);
			// Create a new request to the mentioned URL.    
			WebRequest myWebRequest= WebRequest.Create("http://www.craigscreations.com/cgi-bin/campic.pl");

			// Set the 'Method' prperty  to 'POST' to post data to a Uri.
			myWebRequest.Method="POST";
			myWebRequest.ContentType="application/x-www-form-urlencoded";
			string postData="testmsg=";
			// Convert  the string into a byte array.
			byte[] ByteArray = encoder.GetBytes(postData);
			byteImageArray = encoder.GetBytes(encodedImageString);
			Stream streamRequest;
			try 
			{
				streamRequest = myWebRequest.GetRequestStream();
			}
			catch(System.Net.WebException err) 
			{
				System.Diagnostics.Trace.WriteLine(err.Message);
				return;
			}
			// Write data to the stream.
			streamRequest.Write(ByteArray,0,ByteArray.Length);
			streamRequest.Write(byteImageArray,0,byteImageArray.Length);
			streamRequest.Close();        
			// Assign the response object of 'WebRequest' to a 'WebResponse' variable.
			WebResponse myWebResponse;
			try 
			{
				myWebResponse=myWebRequest.GetResponse();
			}
			catch(System.Net.WebException err) 
			{
				System.Diagnostics.Trace.WriteLine(err.Message);
				return;
			}

			Stream streamResponse=myWebResponse.GetResponseStream();
			StreamReader streamRead = new StreamReader( streamResponse );
			Char[] readBuff = new Char[256];
			int count = streamRead.Read( readBuff, 0, 256 );
			String outputData = "";
			while (count > 0) 
			{
				outputData += new String(readBuff, 0, count);
				Console.Write(outputData);
				count = streamRead.Read(readBuff, 0, 256);
			}
			System.Diagnostics.Trace.WriteLine(outputData);
			// Close the Stream Object.
			streamResponse.Close();
			streamRead.Close();

			// Release the HttpWebResponse Resource.
			myWebResponse.Close();
		}

		private void btnPostPicture_Click(object sender, System.EventArgs e)
		{
			CameraController.SnapPhotoToFile(@"C:\dotnetimage.bmp");
			Bitmap bmpImage = new Bitmap(@"C:\dotnetimage.bmp");
			PostPicture(bmpImage);
		}

		private void btnBringItAllTogether_Click(object sender, System.EventArgs e)
		{
			CameraController.Start(previewVideo.Handle,previewVideo.DisplayRectangle);
			CameraController.TimedPhotoEvent +=new TimedPhotoEventHandler(this.OnTimedPhoto);
			CameraController.SnapTimedPhoto(10000/*1000 60 * 15*/,true);		
			btnBringItAllTogether.Enabled = false;
		}

		private void OnClosing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			CameraController.Stop();
		}
	}
}
