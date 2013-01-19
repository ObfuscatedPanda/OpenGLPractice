use strict;
use warnings;
use Getopt::Long;

#################################################################################
# TYPES
# _X
# 
# 
# 
#################################################################################

my $usage = "This script is a utility that is useful for converting standard 3d
graphics file-types into an engine specific binary format. Currently, the utility
supports the following file extensions:
.X (Direct X)

Script arguments:
-source       The file that needs converting
-destination  (optional) The output file location - save as source name with new 
              extension if file doesn't exist
-type         (optional) The file extension type of the file we are converting
";

my $sourceFile      = "";
my $destinationFile = "";
my $filetype        = "";

GetOptions( 
		"source=s" => 		\$sourceFile,
		"destination=s" => 	\$destinationFile,
		"filetype=s" => 	\$filetype
		);

print "

source: $sourceFile
destination: $destinationFile
filetype: $filetype
";
		
if("" eq $sourceFile)
{
	die("Inproper use of script. See usage:\n $usage");
}

Convert_XFileToBinary($sourceFile);

###############################################################################
# .X Mesh Template
# template Mesh
# {
#     <3D82AB44-62DA-11CF-AB39-0020AF71E433>
#     DWORD nVertices;
#     array Vector vertices[nVertices];
#     DWORD nFaces;
#     array MeshFace faces[nFaces];
#     [...]
# }
#
# template MeshFace
# {
#     < 3D82AB5F-62DA-11cf-AB39-0020AF71E433 >
#     DWORD nFaceVertexIndices;
#     array DWORD faceVertexIndices[nFaceVertexIndices];
# } 

sub Convert_XFileToBinary
{
	my $headerSize = 0; # Size in bytes of the header section
	my @headerEntries = (); 
	## Get the file name 
	my $sourceFile = $_[0];
	my ($sourceFileName, $hasExtension) = $sourceFile =~/\\?(\w+)(\.\w+)?$/;
	my $binaryFilePath;
	if($hasExtension ne "")
	{
		($binaryFilePath) = $sourceFile =~/^(.+)\.\w+$/;
		$binaryFilePath .= ".bf"
	}
	else
	{
		$binaryFilePath = $sourceFile . ".bf";
	}
	
	## JUST FOR CHARACTER FILES
	## Open the file and read it into memory
	print "Opening $sourceFile for read\n";
	print "source file name : $sourceFileName\n";
	open(my $SOURCE_FILE, $sourceFile) or die ("Could not open source file");
	my @sourceFileLines = <$SOURCE_FILE>;
	close($SOURCE_FILE);
	
	## Find the start of the mesh
	my $line = 0;
	for(; $sourceFileLines[$line] !~ /^\s*Mesh\s*(\w+)\s*{/; $line++) {	};
	my $meshName = $1;
	$line++; ## Go to the vert count line
	my ($vertCount) = $sourceFileLines[$line] =~ /(\w+)\s*;/;
	$line++;
	
	## Add to the header section
	print "VERT COUNT $vertCount \n";
	push(@headerEntries, $vertCount * 3);
	$headerSize += 4;
	
	## Get the vertices to build our mesh
	## {x, y, z}
	my @verts = ();
	# 3n elements where n is the number of verts in the {x1, y1, z1, x2, y2, z2, ... , xn, yn, zn}
	my @faces = (); 
	my $doneVerts = 0;
	while(!$doneVerts)
	{
		## TODO: change to use split and implement a counter
		## that can handle a varying number of entries per line (check for a comma)
		my ($x, $y, $z, $delim) = $sourceFileLines[$line] =~ /(\S+);(\S+);(\S+);([;,])/;
		#print "line: $sourceFileLines[$line]
		#x: $x
		#y: $y
		#z: $z
		#delim: $delim
		#";
		if($delim =~ /;/)
		{
			$doneVerts = 1;
		}
		my %vector = ();
		$vector{"X"} = $x;
		$vector{"Y"} = $y;
		$vector{"Z"} = $z;
		push(@verts, \%vector);
		$line++;
	}
	my $vertsNumEntries = @verts;
	print "VERT LINE $line\n";
	print "VERTS $vertsNumEntries\n";
	
	for(; $sourceFileLines[$line] !~ /^\s*(\w+)\s*;\s*$/; $line++) {};
	my ($faceCount) = $sourceFileLines[$line] =~ /^\s*(\w+)\s*;\s*$/;
	$line++;
	#my $faceCount = $1;
	print "FACE COUNT $faceCount\n";
	push(@headerEntries, $faceCount * 3);
	$headerSize += 4;
	my $doneFaces = 0;
	while(!$doneFaces)
	{
		## TODO: change to use split and implement a counter
		## that can handle a varying number of entries per line (check for a comma)
		my $faceCount;
		my @vec = [0, 0, 0];
		my $delim;
		($faceCount, $vec[0], $vec[1], $vec[2], $delim) = $sourceFileLines[$line] =~ /(\w+);(\w+),(\w+),(\w+);([;,])/;
		#print "line: $sourceFileLines[$line]
		#delim: $delim
		#";
		if($delim =~ /;/)
		{
			$doneFaces = 1;
		}
		my %face = ();
		for(my $index = 0; $index < $faceCount; $index++)
		{
			$face{"VERT_$index"} = $vec[$index];
		}
		push(@faces, \%face);
		#push(@ordinatesArray, \%face);
		
		#my @face = ();
		#my $vert1ArrayRef = $verts[$vec1];
		#my @vert1Array = @$vert1ArrayRef;
		#push(@face, $vert1Array[0]); push(@face, $vert1Array[1]); push(@face, $vert1Array[2]);	
		#push(@ordinatesArray, $vert1Array[0]); push(@ordinatesArray, $vert1Array[1]); push(@ordinatesArray, $vert1Array[2]);
		#my $vert2ArrayRef = $verts[$vec2];
		#my @vert2Array = @$vert2ArrayRef;
		#push(@face, $vert2Array[0]); push(@face, $vert2Array[1]); push(@face, $vert2Array[2]);
		#push(@ordinatesArray, $vert2Array[0]); push(@ordinatesArray, $vert2Array[1]); push(@ordinatesArray, $vert2Array[2]);
		#my $vert3ArrayRef = $verts[$vec3];
		#my @vert3Array = @$vert3ArrayRef;
		#push(@face, $vert3Array[0]); push(@face, $vert3Array[1]); push(@face, $vert3Array[2]);
		#push(@ordinatesArray, $vert3Array[0]); push(@ordinatesArray, $vert3Array[1]); push(@ordinatesArray, $vert3Array[2]);
		
		#push(@faces, \@face);
		$line++;
	}
	
	## Find the start of the Texture Coordinates Section
	for(; $sourceFileLines[$line] !~ /^\s*MeshTextureCoords\s*{\s*$/; $line++) {};
	$line++;
	## Skip the entry counter
	for(; $sourceFileLines[$line] !~ /^\s*(\w+)\s*;\s*$/; $line++) {};
	my ($textureCoordinateCount) = $sourceFileLines[$line] =~ /^\s*(\w+)\s*;\s*$/;
	print "TEXTURE COORDINATE COUNT $textureCoordinateCount   from line: $sourceFileLines[$line]\n";
	$line++;
	push(@headerEntries, $textureCoordinateCount * 2);
	$headerSize += 4;
	
	## Get all of the texture coordinates
	my @textureCoordinates = ();
	my $doneTextureCoordinates = 0;
	while(!$doneTextureCoordinates)
	{
		my ($xTextureOrdinate, $yTextureOrdinate, $delim) = $sourceFileLines[$line] =~ /(\S+);(\S+);([;,])/;
		if($delim =~ /;/)
		{
			$doneTextureCoordinates = 1;
		}
		my %textureCoordinate = ();
		$textureCoordinate{"X"} = $xTextureOrdinate;
		$textureCoordinate{"Y"} = $yTextureOrdinate;
		push(@textureCoordinates, \%textureCoordinate);
		$line++;
	}
	
	##################################
	## SECTION IDS
	##
	## 0 - VERTEX COORDINATES
	## 1 - FACE VERTICES
	## 2 - TEXTURE COORDINATES
	## 3 -
	## 4 -
	## 5 -
	## .
	## .
	## .
	
	## Get the faces for the mesh
	print "==================================\nPRINTING FACES\n======================================\n";
	#foreach my $faceVertsArrayRef (@faces)
	#{
	#	my @faceVertsArray = @$faceVertsArrayRef;
	#	print "NewVerts\n";
	#	foreach my $ordinate (@faceVertsArray)
	#	{
	#		#print $BINARY_FILE pack('f*', $ordinate);
	#	}	
	#}
	
	my $sectionFlags = 0;
	$sectionFlags |= 0x1; # We have a vertex section
	$sectionFlags |= (0x1 << 1); # We have a faces section
	$sectionFlags |= (0x1 << 2); # We have a texture coordinates secito
	
	print "SECTION FLAGS $sectionFlags\n";
	
	#PRINT THE BINARY ARRAY
	my @binaryDataArray = ();
	push(@binaryDataArray, $sectionFlags);
	
	## Add the header data
	my $memoryLocationSum = 0;
	my $firstSectionStart = 0;
	my $headerEntryIndex = 0;
	my @sectionStartMemoryLocations = ();
	$memoryLocationSum += @headerEntries;
	$firstSectionStart = ($memoryLocationSum + 1) * 4;
	$memoryLocationSum = ($memoryLocationSum + 1) * 4;# + 4;
	print "FIRST SECTION START $firstSectionStart\n";
	my $entry = 0;
	my $memoryIndex = 4;
	for(; $memoryIndex < $firstSectionStart; $entry++, $memoryIndex += 4)
	{
		if($entry < @headerEntries)
		{
			print "push " . $memoryLocationSum ."\n";
			push(@binaryDataArray, $memoryLocationSum);
			push(@sectionStartMemoryLocations, $memoryLocationSum);
			$memoryLocationSum += ($headerEntries[$entry] + 2) * 4; # Add 4 for the section size value
		}
		else
		{
			push(@binaryDataArray, 0xFFFFFFFF); # Fill the rest of the section with empty data
		}		
	}
	

	## Add the vertex data
	## TODO: USE A HASH TO DETERMINE INDEX IN CASE WE HAVE MISSING TYPES/INFO
	push(@binaryDataArray, $headerEntries[$headerEntryIndex++]);
	for($entry = 0; $memoryIndex < $sectionStartMemoryLocations[1]; $memoryIndex += 12)
	{
		
		if($entry < @verts)
		{
			my $vertsHashRef = $verts[$entry];
			#print "push " . $vertsHashRef->{"X"} ."\n";
			#print "push " . $vertsHashRef->{"Y"} ."\n";
			#print "push " . $vertsHashRef->{"Z"} ."\n";
			push(@binaryDataArray, $vertsHashRef->{"X"});
			push(@binaryDataArray, $vertsHashRef->{"Y"});
			push(@binaryDataArray, $vertsHashRef->{"Z"});
			$entry++;
		}
		else
		{
			#print "push 0xFFFF\n";
			push(@binaryDataArray, 0xFFFFFFFF);
		}
	}
	if($entry >= @verts)
	{
		print "ENTRY > VERTS $entry\n";
	}
	else
	{
		print "MEMORY INDEX > SECTIONSTARTMEMORYLOCATIONS[1]\n";
	}
	
	## Add the face data
	push(@binaryDataArray, $headerEntries[$headerEntryIndex++]);
	for($entry = 0; $memoryIndex < $sectionStartMemoryLocations[2]; $memoryIndex += 12, $entry++)
	{	
		if($entry < @faces)
		{
			my $faceRef = $faces[$entry];
			for(my $index = 0; $index < 3; $index += 1)
			{
				#print "push  " . $faceRef->{"VERT_$index"} . "\n";
				push(@binaryDataArray, $faceRef->{"VERT_$index"});
			}
		}
		else
		{
			#print "push 0xFFFF\n";
			push(@binaryDataArray, 0xFFFFFFFF);
		}
	}
	
	## Add the texture coordinate data
	#for($entry = 0; $memoryIndex < $sectionStartMemoryLocations[3]; $memoryIndex += 4, $entry++)
	#{
	push(@binaryDataArray, $headerEntries[$headerEntryIndex++]);
	for($entry = 0; $entry < @textureCoordinates; $memoryIndex += 8, $entry++)
	{
		if($entry < @textureCoordinates)
		{
			my $textureCoordinateHashRef = $textureCoordinates[$entry];
			#print "push " . $textureCoordinateHashRef->{"X"} . "\n";
			#print "push " . $textureCoordinateHashRef->{"Y"} . "\n";
			push(@binaryDataArray, $textureCoordinateHashRef->{"X"});
			push(@binaryDataArray, $textureCoordinateHashRef->{"Y"});
		}
		else
		{
			push(@binaryDataArray, 0xFFFFFFFF);
		}
	}
	
	my $binaryDataArraySize = @binaryDataArray;
	print "___ $binaryDataArraySize	$sectionStartMemoryLocations[0] $sectionStartMemoryLocations[1] $sectionStartMemoryLocations[2]\n";
	
	print "START MEM LOCATIONS @sectionStartMemoryLocations\n";
	print "VERT 1 \
	\t$binaryDataArray[($sectionStartMemoryLocations[0] / 4)] \
	\t$binaryDataArray[($sectionStartMemoryLocations[0] / 4) + 1] \
	\t$binaryDataArray[($sectionStartMemoryLocations[0] / 4) + 2] \
	\t$binaryDataArray[($sectionStartMemoryLocations[0] / 4) + 3]\n";
				  
	print "FACE 1 
	\t$binaryDataArray[($sectionStartMemoryLocations[1] / 4)]
	\t$binaryDataArray[($sectionStartMemoryLocations[1] / 4) + 1] 
	\t$binaryDataArray[($sectionStartMemoryLocations[1] / 4) + 2] 
	\t$binaryDataArray[($sectionStartMemoryLocations[1] / 4) + 3]\n";
				  
	print "TEX 1 \
	\t$binaryDataArray[($sectionStartMemoryLocations[2] / 4)] \
	\t$binaryDataArray[($sectionStartMemoryLocations[2] / 4) + 1] \
	\t$binaryDataArray[($sectionStartMemoryLocations[2] / 4) + 2]\n";
				  
	print "BINARY DATA ARRAY\n@binaryDataArray\n ////BINARY DATA ARRAY\n";
	
	open(my $BINARY_FILE, '>:raw', $binaryFilePath) or die("Couldn't open a destination file");
	print $BINARY_FILE pack('f*', @binaryDataArray); #ordinates array
	my @floatArray = unpack ('f*', pack('f*', @binaryDataArray));#ordinatesArray)); 
	print "$floatArray[0], $floatArray[1], $floatArray[2].\n";
	close($BINARY_FILE);
}

sub ParseSectionNames_X_File
{

}

sub ParseVerts_X_File
{

}

sub ParseFaces_X_File
{


}

sub ParseTextureCoords_X_File
{

}

sub PrintBinaryFileFromXFile
{

}