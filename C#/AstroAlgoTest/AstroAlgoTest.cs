using TAGDigitalStudios.AstroAlgo;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;

namespace AstroAlgoTest
{
    
    
    /// <summary>
    ///This is a test class for AstroAlgoTest and is intended
    ///to contain all AstroAlgoTest Unit Tests
    ///</summary>
	[TestClass()]
	public class AstroAlgoTest
	{


		private TestContext testContextInstance;

		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		public TestContext TestContext
		{
			get
			{
				return testContextInstance;
			}
			set
			{
				testContextInstance = value;
			}
		}

		#region Additional test attributes
		// 
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//public static void MyClassInitialize(TestContext testContext)
		//{
		//}
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//public static void MyClassCleanup()
		//{
		//}
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//public void MyTestInitialize()
		//{
		//}
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//public void MyTestCleanup()
		//{
		//}
		//
		#endregion


		/// <summary>A test for MoonPhases</summary>
		[TestMethod()]
		public void MoonPhasesTest()
		{
			AstroAlgo target = new AstroAlgo();
			AstroAlgo.MoonPhase phase = AstroAlgo.MoonPhase.FullMoon;

			List<DateTime> actual;

			actual = target.MoonPhases(phase);

			Assert.IsTrue(actual.Count > 0, "SOmething");
		}

		/// <summary>A test for Sun rise/set</summary>
		[TestMethod()]
		public void RiseSetTranTest()
		{
			int month = 7;			// month
			double day = 8.0;			// day
			int year = 2000;		// year
			double L = 95.0950;		// longitude
			double phi = 29.5070;		// latitude

			double JD;					// Julian Day
			double m0;					// transit time
			double m1;					// rise time
			double m2;					// set time
			double[] alpha = new double[3];				// right ascension
			double[] delta = new double[3];				// declination
			double A;					// azimuth
			double h;					// altitude

			AstroAlgo target = new AstroAlgo();

			TimeSpan ts = TimeSpan.FromDays(day);
			
			JD = AstroAlgo.Date2Julian(new DateTime(year, month, ts.Days, ts.Hours, ts.Minutes, ts.Seconds));
			AstroAlgo.ApparentSolarCoordinates(JD, out alpha[1], out delta[1]);
			AstroAlgo.ApparentSolarCoordinates(JD-1, out alpha[0], out delta[0]);
			AstroAlgo.ApparentSolarCoordinates(JD+1, out alpha[2], out delta[2]);
			double[] m = AstroAlgo.RiseTranSet(L, phi, -0.8333, JD, alpha, delta);

			TimeSpan tsRise = AstroAlgo.Fraction2Time(m[1]);
			//AstroAlgo.AzimuthAltitude(JD + m[1], alpha, delta, L, phi, out A, out h);

			int x = 5;
			//Assert.IsTrue(actual.Count > 0, "SOmething");
		}
	}
}
