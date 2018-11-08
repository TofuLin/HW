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
        
public class Copy {
        
 public static class Map extends Mapper<LongWritable, Text, Text, Text> {    
private String[] datas;
private String Date;
private String City;
private String Type;
private String N1;
private String N2;
private String N3;
private String N4;
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
	//N4=datas[6];
	//Text pm=new Text(Date+","+City+","+Type+","+N1+","+N2+","+N3+","+N4);
	String ss=(new StringBuilder().append(N1).append(",").append(N2).append(",").append(N3).append(",").toString());
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
    job.setJarByClass(WordCount.class);
        
    job.setInputFormatClass(TextInputFormat.class);
    job.setOutputFormatClass(TextOutputFormat.class);
        
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
        
    job.waitForCompletion(true);
 }
        
}
