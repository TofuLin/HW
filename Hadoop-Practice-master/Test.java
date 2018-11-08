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
        
public class Test {
        
 public static class Map extends Mapper<LongWritable, Text, Text, Text> {
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
	String[] data=value.toString().split(",");
	String Date=data[0];
	String City=data[1];
	String Type=data[2];
	String N1=data[3].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
	String N2=data[4].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
        context.write(new Text(""),new Text(Date+","+City+","+Type+","+N1+","+N2));
	}
}
// public static class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {
//private IntWritable result = new IntWritable();
  //  public void reduce(Text key, Iterable<IntWritable> values, Context context) 
    //  throws IOException, InterruptedException {
      //  context.write(key, result);
   // }
// }
        
 public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
        
        Job job = new Job(conf, "test");
    
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);
        
    job.setMapperClass(Map.class);
//    job.setReducerClass(Reduce.class);
    job.setJarByClass(WordCount.class);
        
    job.setInputFormatClass(TextInputFormat.class);
    job.setOutputFormatClass(TextOutputFormat.class);
        
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
        
    job.waitForCompletion(true);
 }
        
}
