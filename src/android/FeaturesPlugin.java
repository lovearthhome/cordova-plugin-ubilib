package com.ydcun.ivita.util;
import org.apache.cordova.CallbackContext;  
import org.apache.cordova.CordovaPlugin;  
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException; 
import java.util.ArrayList;


public class FeaturesPlugin extends CordovaPlugin {
	public static final String ACTION_GP = "getParams";
	public static final String ACTION_GP2 = "getParams2";
	public static final String ACTION_FFT = "fft";
	public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
		if (ACTION_GP.equals(action)) {
			JSONArray arg0 =args.getJSONArray(0);
			int len=arg0.length();
			double [] Xs = new double[len];
			double [] Ys = new double[len];
			double [] Zs = new double[len];
			double [] As = new double[len];
			for(int i=0;i<len;i++){
				JSONObject acc=arg0.getJSONObject(i);
				double x=Double.parseDouble(acc.getString("x"));
				double y=Double.parseDouble(acc.getString("y"));
				double z=Double.parseDouble(acc.getString("z"));
				
				Xs[i]=x;
				Ys[i]=y;
				Zs[i]=z;
				As[i]=Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2) + Math.pow(z, 2));
			}
			//不要修改以上的代码
			//接下来的代码调用Features.java来获取数组As,Xs,Ys,Zs的各种特征值

			double min =Features.minimum(As);
			
			double max =Features.maximum(As);
			
			double mcr = Features.meanCrossingsRate(As);

			double dev =Features.standardDeviation(As);



			double[] fft=Features.fft(As);

			double spp=Features.spp(fft);

			double entropy =Features.entropy(fft); //FFT

			double energy =Features.energy(fft); //FFT

			double centroid =Features.centroid(fft); //FFT

		
			JSONArray ja=new JSONArray();
			JSONObject jo = new JSONObject();
			jo.put("min",min);
			jo.put("max",max);
			jo.put("mcr",mcr);
			jo.put("dev",dev);
			jo.put("entropy",entropy);
			jo.put("energy",energy);
			jo.put("centroid",centroid);
			jo.put("spp",spp);
			ja.put(jo);
			//不要修改以下的代码
			callbackContext.success(ja);
			return true;
		}else if (ACTION_GP2.equals(action)) {
			JSONArray arg0 =args.getJSONArray(0);
			double[] As = new double[128];
			for (int i = 0; i < arg0.length(); i++) {
				As[i] = arg0.getDouble(i);
			}

			double min =Features.minimum(As);
			
			double max =Features.maximum(As);

			double mean =Features.mean(As);
			
			double mcr = Features.meanCrossingsRate(As);

			double dev =Features.standardDeviation(As);

			double[] fft=Features.fft(As);

			JSONArray fftArray=new JSONArray();
			for(int i=0;i<fft.length;i++){
				fftArray.put(fft[i]);
			}

			double spp=Features.spp(fft);

			double entropy =Features.entropy(fft); //FFT

			double energy =Features.energy(fft); //FFT

			double centroid =Features.centroid(fft); //FFT

		
			JSONArray ja=new JSONArray();
			JSONObject jo = new JSONObject();
			jo.put("min",min);
			jo.put("max",max);
			jo.put("mean",mean);
			jo.put("mcr",mcr);
			jo.put("dev",dev);
			jo.put("entropy",entropy);
			jo.put("energy",energy);
			jo.put("centroid",centroid);
			jo.put("spp",spp);
			ja.put(jo);
			ja.put(fftArray);
			//不要修改以下的代码
			callbackContext.success(ja);
			return true;
		}else if (ACTION_FFT.equals(action)) {
			//JSONArray	put(double value) :  Append a double value.
			JSONArray arg0 =args.getJSONArray(0);
			double[] accArray = new double[128];
			for (int i = 0; i < arg0.length(); i++) {
				accArray[i] = arg0.getDouble(i);
			}
			double [] fftData = Features.fft(accArray);
			JSONArray ja=new JSONArray();
			for(int i=0;i<fftData.length;i++)
				ja.put(fftData[i]);
			callbackContext.success(ja);
		}
		callbackContext.error("failure");
		return false;
	}
/*
	public double[] fft(JSONArray list) {
		int len=list.length();
		Complex[] theList = new Complex[2*len];
		for (int i = 0; i < len; i++) {
			theList[i] = new Complex(list[i], 0);
		}
		for (int i = len; i < 2*len; i++) {
			theList[i] = new Complex(0, 0);
		}
		
		// fft
		Complex[] Y = FFT.fft(theList);
		
		// 
		for (int i = 0; i < Y.length; i++) {
			Y[i] = Y[i].times(1/len);
		}
		
		double[] fftSeries = new double[len/2];
		for (int i = 1, j = 0; i < len/2 + 1; i++, j++) {
			fftSeries[j] = 2 * theList[i].abs();
		}
	
		return fftSeries;
	}
	*/
}