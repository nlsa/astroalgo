using System;
using System.Collections.Generic;
using System.Text;

namespace TAGDigitalStudios.AstroAlgo
{
	public struct Angle
	{
		private int degree;
		private int arcmin;
		private double arcsec;

		public Angle( int d, int m, double s )
		{
			if ( m < 0 || m > 59 )
				throw new System.ArgumentOutOfRangeException( "minute", "Must be a integer between 0 and 59 inclusive.)" );

			if ( s < 0.0 || !( s < 60.0 ) )
				throw new System.ArgumentOutOfRangeException( "second", "Must be a double in the domain [0.0,60.0)" );

			this.degree = d;
			this.arcmin = m;
			this.arcsec = s;
		}

		public Angle( double value )
		{
			this.degree = (int)Math.Truncate( value );
			double fracMin = ( value - this.degree ) * 60.0;
			this.arcmin = (int)Math.Truncate( fracMin );
			this.arcsec = ( fracMin - this.arcmin ) * 60.0;
		}

		public double FractionalDegrees
		{
			get
			{
				return this.degree + ( this.arcmin + this.arcsec / 60.0 ) / 60.0;
			}
		}

		public int Hour
		{
			get { return (int)Math.Truncate( this.degree / 15.0 ); }
		}

		public int Degree
		{
			get { return this.degree; }
		}

		public int ArcMinute
		{
			get { return this.arcmin; }
		}

		public double ArcSecond
		{
			get { return this.arcsec; }
		}

	}
}
