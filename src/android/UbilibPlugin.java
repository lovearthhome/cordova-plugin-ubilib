package com.ydcun.ivita.util;
import org.apache.cordova.CallbackContext;  
import org.apache.cordova.CordovaPlugin;  
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException; 
import java.util.ArrayList;


public class UbilibPlugin extends CordovaPlugin {
	public static final String ACTION_GP = "getParams";
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
			double[] fft=Features.fft(As);
			double min =Features.minimum(As);
			double max =Features.maximum(As);
			double mcr = Features.meanCrossingsRate(As);
			double dev =Features.standardDeviation(As);
			double rms =Features.rms(As);//均方根平均值
			double sma =Features.sma(As,4.0/128.0);//信号幅值面
			double iqr =Features.iqr(As);//四分卫距
			double mad =Features.mad(As);//绝对平均差
			double mean =Features.mean(As);//平均值
			double median =Features.median(As);//中位数
			double tenergy =Features.tenergy(As); //FFT
			double spp=Features.spp(fft);
			double entropy =Features.entropy(fft); //FFT
			double energy =Features.energy(fft); //FFT
			double centroid =Features.centroid(fft); //FFT
			double fdev =Features.standardDeviation(fft); //FFT
			double fmean =Features.mean(fft); //FFT
			double skew =Features.skew(fft); //FFT
			double kurt =Features.kurt(fft); //FFT

		
			JSONArray ja=new JSONArray();
			JSONObject jo = new JSONObject();
			jo.put("min",min);
			jo.put("max",max);
			jo.put("mcr",mcr);
			jo.put("dev",dev);
			jo.put("rms",rms);
			jo.put("sma",sma);
			jo.put("iqr",iqr);
			jo.put("mad",mad);
			jo.put("mean",mean);
			jo.put("median",median);
			jo.put("tenergy",tenergy);
			jo.put("entropy",entropy);
			jo.put("energy",energy);
			jo.put("centroid",centroid);
			jo.put("spp",spp);
			jo.put("fdev",fdev);
			jo.put("fmean",fmean);
			jo.put("skew",skew);
			jo.put("kurt",kurt);

			ja.put(jo);
			
			JSONArray asArray=new JSONArray();
			for(int i=0;i<As.length;i++){
				asArray.put(As[i]);
			}
			ja.put(asArray);
			JSONArray fftArray=new JSONArray();
			for(int i=0;i<fft.length;i++){
				fftArray.put(fft[i]);
			}
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

}
