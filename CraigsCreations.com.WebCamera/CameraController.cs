using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;

namespace CraigsCreations.com.WebCamera
{
	public delegate void TimedPhotoEventHandler(Bitmap image);

	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class CameraController
	{
		[DllImport("ShutterBug.dll")]
		private static extern void CameraStart(IntPtr hWnd,int left, int top, int right, int bottom);
		[DllImport("ShutterBug.dll")]
		private static extern void CameraSnapPhotoToFile(String szFileName);
		[DllImport("ShutterBug.dll")]
		private static extern void CameraSnapPhoto(ref IntPtr image, ref long imageLength);
		[DllImport("ShutterBug.dll")]
		private static extern void CameraStop();

		private static System.Threading.Timer timedPhoto = null;
		private static System.Threading.TimerCallback timerDelegate = new TimerCallback(OnTimedPhoto);
		
		public static event TimedPhotoEventHandler TimedPhotoEvent;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="fileName"></param>
		private static void OnTimedPhoto(object state) 
		{
			byte[] imageByteArray = SnapPhoto();
			if(null==imageByteArray) 
			{
				return;
			}

			MemoryStream imageStream = new MemoryStream(imageByteArray);
			try 
			{
				Bitmap image = new Bitmap(imageStream);
				TimedPhotoEvent(image);
			} 
			catch(System.Exception err) 
			{
				System.Diagnostics.Trace.WriteLine(err.Message);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="rc"></param>
		public static void Start(IntPtr hWnd, Rectangle rc)
		{
			CameraStart(hWnd,rc.Left,rc.Top,rc.Right,rc.Bottom);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="rc"></param>
		public static void Start()
		{
			CameraStart(IntPtr.Zero,0,0,0,0);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="fileName"></param>
		public static void SnapPhotoToFile(String fileName) 
		{
			CameraSnapPhotoToFile(fileName);
		}
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="image"></param>
		public static byte[] SnapPhoto() 
		{
			long imageLength = 0;
			IntPtr imagePointer = IntPtr.Zero;
			CameraSnapPhoto(ref imagePointer,ref imageLength);
			byte[] image  = null;
			if(0 < imageLength) 
			{
				image = new byte[ imageLength ];
				if(imagePointer != IntPtr.Zero) 
				{
					Marshal.Copy( imagePointer, image, 0, (int) imageLength );
				}
			} 
			return(image);
		}

		public static void SnapTimedPhoto(int msWaitTime,bool isRepetitive) 
		{
			OnTimedPhoto(null);
			int repeat = (isRepetitive) ? Timeout.Infinite : 0;
			if(null != timedPhoto) { 
				timedPhoto.Dispose();
				timedPhoto = null; 
			}
			timedPhoto = new System.Threading.Timer(timerDelegate,null,10000,msWaitTime);
		}
		
		/// <summary>
		/// 
		/// </summary>
		public static void Stop()
		{
			if(null != timedPhoto) 
			{ 
				timedPhoto.Dispose();
				timedPhoto = null; 
			}
			CameraStop();		
		}
	}
}
