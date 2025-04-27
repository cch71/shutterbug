package CraigsCreations.com.WebCamera;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.util.*;
import CraigsCreations.com.WebCamera.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */
public class ServerImageViewer extends Applet {
  private boolean isStandalone = false;
  ServerImageViewer imageViewer = null;
  String serverURL;
  long updateTimer;
  Image webPicture = null;
  Timer timerRefreshPicture;

  class ImageRefreshTask extends TimerTask {
    public void run() {
      webPicture = getImage(getCodeBase(), serverURL);
      if( (null!=webPicture) && (null!=imageViewer) && (0!=imageViewer.getWidth()) ) {
        webPicture = webPicture.getScaledInstance(imageViewer.getWidth(),
                                                  imageViewer.getHeight(),
                                                  Image.SCALE_DEFAULT);
        Graphics graphics = imageViewer.getGraphics();
        if(null!=graphics) {
          graphics.drawImage(webPicture, 0, 0, imageViewer);
          imageViewer.update(graphics);
 //         System.out.println("Updating Image " + System.currentTimeMillis());
        }
      }

    }

  }

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public ServerImageViewer() {
  }
  //Initialize the applet
  public void init() {
    imageViewer = this;
    try {
      serverURL = this.getParameter("URL", "http://www.craigscreations.com/images/campic.jpg");
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    try {
      updateTimer = Long.parseLong(this.getParameter("UpdateTimer", "10000"));
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
    try {
      timerRefreshPicture = new Timer();
      timerRefreshPicture.scheduleAtFixedRate(new ImageRefreshTask(),0,updateTimer);
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  //Component initialization
  private void jbInit() throws Exception {
  }
  //Start the applet
  public void start() {
    if(null!=webPicture) {
      webPicture = webPicture.getScaledInstance(this.getWidth(), this.getHeight(),
                                                Image.SCALE_DEFAULT);

    }
  }

  public void paint(Graphics graphics) {
    if(null!=webPicture) {
      graphics.drawImage(webPicture, 0, 0, this);
//      System.out.println("Painting " + System.currentTimeMillis());
    }
  }
  //Stop the applet
  public void stop() {
    timerRefreshPicture.cancel();
  }
  //Destroy the applet
  public void destroy() {
  }
  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }
  //Get parameter info
  public String[][] getParameterInfo() {
    String[][] pinfo =
      {
      {"URL", "String", ""},
      {"UpdateTimer", "long", ""},
      };
    return pinfo;
  }
  //Main method
  public static void main(String[] args) {
    ServerImageViewer applet = new ServerImageViewer();
    applet.isStandalone = true;
    Frame frame;
    frame = new Frame();
    frame.setTitle("Applet Frame");
    frame.add(applet, BorderLayout.CENTER);
    applet.init();
    applet.start();
    frame.setSize(400,320);
    Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
    frame.setLocation((d.width - frame.getSize().width) / 2, (d.height - frame.getSize().height) / 2);
    frame.setVisible(true);
  }
}