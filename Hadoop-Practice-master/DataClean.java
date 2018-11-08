//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		No more bug please!!!!!!!
import java.io.IOException;
import java.util.*;
        
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
        
public class DataClean {
        
 public static class Map extends Mapper<LongWritable, Text, Text, Text> {    
private String[] datas;
private String Date;
private String City;
private String Type;
private String N1;
private String N2;
private String N3;
private String N4;
private String N5;
private String N6;
private String N7;
private String N8;
private String N9;
private String N10;
private String N11;
private String N12;
private String N13;
private String N14;
private String N15;
private String N16;
private String N17;
private String N18;
private String N19;
private String N20;
private String N21;
private String N22;
private String N23;
private String N24;
public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
	datas=value.toString().split(",");
	Date=datas[0];
	City=datas[1];
	Type=datas[2];
//	for(int i=3;i<27;i++){
//	Number[i-3]=datas[i].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
//	if(Number[i].equals("")){Number[i]="0";}
//
//	}
	N1=datas[3].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
	if(N1.equals("")){N1="0";}
	N2=datas[4].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
	if(N2.equals("")){N2="0";}
	N3=datas[5].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
	if(N3.equals("")){N3="0";}
	N4=datas[6].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
	if(N4.equals("")){N4="0";}
	N5=datas[7].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N5.equals("")){N5="0";}
        N6=datas[8].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N6.equals("")){N6="0";}
        N7=datas[9].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N7.equals("")){N7="0";}
        N8=datas[10].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N8.equals("")){N8="0";}
	N9=datas[11].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N9.equals("")){N9="0";}
        N10=datas[12].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N10.equals("")){N10="0";}
        N11=datas[13].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N11.equals("")){N11="0";}
        N12=datas[14].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N12.equals("")){N12="0";}
	N13=datas[15].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N13.equals("")){N13="0";}
        N14=datas[16].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N14.equals("")){N14="0";}
        N15=datas[17].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N15.equals("")){N15="0";}
        N16=datas[18].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N16.equals("")){N16="0";}
	N17=datas[19].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N17.equals("")){N17="0";}
        N18=datas[20].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N18.equals("")){N18="0";}
        N19=datas[21].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N19.equals("")){N19="0";}
        N20=datas[22].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N20.equals("")){N20="0";}
	N21=datas[23].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N21.equals("")){N21="0";}
        N22=datas[24].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N22.equals("")){N22="0";}
        N23=datas[25].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N23.equals("")){N23="0";}
        N24=datas[26].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        if(N24.equals("")){N24="0";}
	//Text pm=new Text(Date+","+City+","+Type+","+N1+","+N2+","+N3+","+N4);
	String ss=(new StringBuilder().append(N1).append(",").append(N2).append(",").append(N3).append(",").append(N4).append(",").append(N5).append(",").append(N6).append(",").append(N7).append(",").append(N8).append(",").append(N9).append(",").append(N10).append(",").append(N11).append(",").append(N12).append(",").append(N13).append(",").append(N14).append(",").append(N15).append(",").append(N16).append(",").append(N17).append(",").append(N18).append(",").append(N19).append(",").append(N20).append(",").append(N21).append(",").append(N22).append(",").append(N23).append(",").append(N24).toString());
//	N4=datas[6].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
//	if(N4.equals("")){N4="0";}
	context.write(new Text(ss),new Text(""));
	//context.write(new Text(""),new Text(Date+","+City+","+Type+","+Number+","));
}
}
// public static class Reduce extends Reducer<Text, Text, Text, Text> {
  //  public void reduce(Text key, Iterable<Text> values, Context context) 
    //  throws IOException, InterruptedException {
      //  context.write(key, new Text());
   // }
// }
        
 public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
        
        Job job = new Job(conf, "test");
    
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);
        
    job.setMapperClass(Map.class);
  //  job.setReducerClass(Reduce.class);
    job.setNumReduceTasks(0);
    job.setJarByClass(WordCount.class);
        
    job.setInputFormatClass(TextInputFormat.class);
    job.setOutputFormatClass(TextOutputFormat.class);
        
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
        
    job.waitForCompletion(true);
 }
        
}
