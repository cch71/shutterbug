using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Diagnostics;
using System.ServiceProcess;
using System.Threading;
using System.Net;
using System.IO;
using System.Text;
using CraigsCreations.com.WebCamera;

namespace ShutterBugService
{
	public class ShutterBugSvc : System.ServiceProcess.ServiceBase
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;


		public ShutterBugSvc()
		{
			// This call is required by the Windows.Forms Component Designer.
			InitializeComponent();

		}

		// The main entry point for the process
		static void Main()
		{
			System.ServiceProcess.ServiceBase[] ServicesToRun;
	
			// More than one user Service may run within the same process. To add
			// another service to this process, change the following line to
			// create a second service object. For example,
			//
			//   ServicesToRun = new System.ServiceProcess.ServiceBase[] {new Service1(), new MySecondUserService()};
			//
			ServicesToRun = new System.ServiceProcess.ServiceBase[] { new ShutterBugSvc() };

			System.ServiceProcess.ServiceBase.Run(ServicesToRun);
		}

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// ShutterBugSvc
			// 
			this.ServiceName = "ShutterBugService";

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

		/// <summary>
		/// Set things in motion so your service can do its work.
		/// </summary>
		protected override void OnStart(string[] args)
		{
			CameraController.Start();
			CameraController.TimedPhotoEvent +=new TimedPhotoEventHandler(this.OnTimedPhoto);
			string strTimeout = System.Configuration.ConfigurationSettings.AppSettings["PictureDelay"];
			CameraController.SnapTimedPhoto(int.Parse(strTimeout),true);		
		}
 
		/// <summary>
		/// Stop this service.
		/// </summary>
		protected override void OnStop()
		{
			CameraController.Stop();
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
			WebRequest myWebRequest= WebRequest.Create(System.Configuration.ConfigurationSettings.AppSettings["WebServerPath"]);

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

	}
}
