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
        
public class R {
        
public static class Map extends Mapper<Object, Text, Text, Text> {    
public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
	String line=value.toString();
	String newline=line.replaceAll("[-+#%x*]","");
	String a=",,";
	String b=",0,";
	String c="NR";
	String d="0";
	String finalline=newline.replace(a,b);
	String finalone=finalline.replace(c,d);
//	N1=datas[3].replaceAll("[\\pP\\p{Punct}a-zA-Z]","");
//	if(N1.equals("")){N1="0";}
	context.write(new Text(finalone.toString()),new Text(""));
}
}
        
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
