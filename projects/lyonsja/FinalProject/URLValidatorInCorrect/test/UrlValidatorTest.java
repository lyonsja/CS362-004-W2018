

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, 1);
	   String str1 = "http://somevalidurl.com";
	   String str2 = "htp:/invalidurl.";
	   String str3 = "file:///somefile";
	   assertTrue(urlVal.isValid(str1));
	   assertTrue(!urlVal.isValid(str2));
	   assertTrue(urlVal.isValid(str3));
	   
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   UrlValidator urlVal2 = new UrlValidator(null, null, 1);
	   String str4 = "HTTP://SomeurlThatWorks.Org";
	   assertTrue(urlVal2.isValid(str4));
	   
	   String str5 = "https:/thisurlisbad.something";
	   assertTrue(urlVal2.isValid(str5));
	   
	   String str6 = "h3t://anotherUrl.org";
	   assertTrue(urlVal2.isValid(str6));
	   
	   String str7 = "https://Acapitalletter.com";
	   assertTrue(urlVal2.isValid(str7));
	   
	   String str8 = "Https://lowercasebody.org";
	   assertTrue(urlVal2.isValid(str8));
	   
	   assertTrue(!urlVal2.isValid("null"));
	   
	   assertTrue(!urlVal2.isValid("http://259.259.259"));
	   
	   assertTrue(urlVal2.isValid("http://166.179.200"));
	   
	   //Alpanumeric character combination in URL
	   assertTrue(urlVal2.isValid("http://url7.com"));
	   
	   assertTrue(urlVal2.isValid("166.154.232"));
	   
	   
   }
   
   public static void Main(String[] argv){
	   
	 
	   
	   
   }


}
