

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
	   UrlValidator urlVal = new UrlValidator(null, null, 1);
	   assertTrue(urlVal.isValid("http://aurl.org"));
   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   
	   UrlValidator urlVal = new UrlValidator(null, null, 1);
	   assertTrue(urlVal.isValid("ftp://anotherurl.com"));
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   UrlValidator urlVal2 = new UrlValidator(null, null, 1);
	   String str4 = "HTTP://SomeurlThatShouldWork.Org";
	   assertTrue(urlVal2.isValid(str4));
	   
	   String str5 = "https:/thisurlisbad.something";
	   assertTrue(urlVal2.isValid(str5));
	   
	   String str6 = "h3t://anotherUrl.org";
	   assertTrue(urlVal2.isValid(str6));
	   
	   //Testing a single capital character in the URL
	   String str7 = "https://Acapitalletter.com";
	   assertTrue(urlVal2.isValid(str7));
	   
	   //Testing single capital character in scheme section of URL"
	   String str8 = "Https://lowercasebody.org";
	   assertTrue(urlVal2.isValid(str8));
	   
	   //Testing null case
	   assertTrue(!urlVal2.isValid("null"));
	   
	   assertTrue(!urlVal2.isValid("http://259.259.259"));
	   
	   assertTrue(urlVal2.isValid("http://166.179.200"));
	   
	   //Alphanumeric character combination in URL
	   assertTrue(urlVal2.isValid("http://url7.com"));
	   
	   //IP-address type URL
	   assertTrue(urlVal2.isValid("166.154.232"));
	   
	   //Scheme (in this case http) in the middle part of the URL
	   assertTrue(urlVal2.isValid("aurl.http://someUrl"));
	   
	   
   }
   
   public static void Main(String[] argv){
	   
	 
	   
	   
   }


}
