
/// @since  x.y.z, 02.04.2017  (integration into Celma)
/// @since  31.12.2002  (original implementation)
template< typename T> class BalancedBinaryTree
{
public:
   /// @since  x.y.z, 02.04.2017
   BalancedBinaryTree();
   BalancedBinaryTree( const BalancedBinaryTree& other);
   BalancedBinaryTree( BalancedBinaryTree&& other);
   ~BalancedBinaryTree();


/*============================================================================
 Description    : t_ReneTree< T>::Insert( data): Status

    Insert the data in 'data' in the tree.

 Parameter      :
    data: the data to insert in the tree

 Return value   : true when the data could be inserted, false otherwise.
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
bool Insert( const T& data);


/*============================================================================
 Description    : t_ReneTree< T>::Delete(): Status

    Deletes the current data in the tree. This means that the data must be
    located before using 'Find' or 'First/Next/Prev/Last'!

 Parameter      : --

 Return value   : true when the data could be deleted, false otherwise.
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
bool Delete( void);


/*============================================================================
 Description    : t_ReneTree< T>::Find( data): dataPtr

    Searches the data in 'data' in the tree and returns a pointer to them if
    found. Subsequently the tree can be scanned using 'Prev/Next' or the
    data deleted using 'Delete'.

 Parameter      :
    data: Pointer to the data buffer

 Return value   : dataPtr: Pointer to the data or NULL if not found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
T* Find( const T& data);


/*============================================================================
 Description    : t_ReneTree< T>::First(): dataPtr

    Locates the first data in the tree.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
T* First( void);


/*============================================================================
 Description    : t_ReneTree< T>::Next(): dataPtr

    Locates the next data in the tree. 'First' or 'Find' must have been used
    before.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
T* Next( void);


/*============================================================================
 Description    : t_ReneTree< T>::Prev(): dataPtr

    Locates the previous data in the tree. 'Find' or 'Last' must have been
    used before.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
T* Prev( void);


/*============================================================================
 Description    : t_ReneTree< T>::Last(): dataPtr

    Locates the last data in the tree.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
T* Last( void);


/*============================================================================
 Description    : t_ReneTree< T>::Info( longPath, average): Status

    Returns information about the state of the rene-tree.
    longPath = maximum depth of the tree (ideally 2log( elements)
    average  = average path length = sum of all path-lengths / elements

 Parameter      :
    longPath: returns the longest path to an element
    average:  returns the average path length

 Return value   : Status: -1 or the number of elements in the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Info( long int& longPath, double& average);


/*============================================================================
 Description    : t_ReneTree< T>::Write( toFile, doDelete): Status

    Stores the data of a rene-tree in a the file 'filename'.
    If 'doDelete' is set (true) the tree contents are deleted.
    That's why the address of the pointer to the tree must be passed. After
    deleting the pointer is NULL.

 Parameter      :
    toFile:   the name of the file to store the tree in
    doDelete: true = delete the tree, false = store only

 Return value   : Status: ERROR (-1) or number of data written
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Write( c_File& toFile, bool doDelete);


/*============================================================================
 Description    : t_ReneTree< T>::Read( fromFile): success

    Reads a rene-tree from the file 'fromFile'. Any data previously stored
    in the tree is deleted.

 Parameter      :
    fromFile: the name of the file to read the tree from.

 Return value   : success: true when the tree could be read, false otherwise
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
bool Read( c_File& fromFile);


/*============================================================================
 Description    : t_ReneTree< T>::DeleteAll()

    Deletes a rene-tree.

 Parameter      : --

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
void DeleteAll( void);


/*============================================================================
 Description    : t_ReneTree< T>::Entries(): numEntries

    Returns the number of entries in the tree.

 Parameter      : --

 Return value   : numEntries: the number of entries in the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Entries( void) const;


/*============================================================================
 Description    : t_ReneTree< T>::Inserted(): numInserted

    Returns the number of entires inserted into the tree. As long as no entry
    is deleted, this equals to the number of entries.

 Parameter      : --

 Return value   : numInserted: the number of entries inserted into the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Inserted( void) const;


/*============================================================================
 Description    : t_ReneTree< T>::Deleted(): numDeleted

    Returns the number of entries that were deleted from the tree.

 Parameter      : --

 Return value   : numDeleted: the number of entries that were deleted
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Deleted( void) const;


/*============================================================================
 Description    : t_ReneTree< T>::Reorgs(): numReorgs

    Returns the number of tree-internal reorganisations.

 Parameter      : --

 Return value   : numReorgs: the number of tree-internal reorganisations
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 =============================================================================*/
int Reorgs( void) const;

private:
   t_RT_Elem< T>* GetGreater( t_RT_Elem< T>* ab, t_RT_Elem< T>* act_x, int level) const;
   t_RT_Elem< T>* GetSmaller( t_RT_Elem< T>* ab, t_RT_Elem< T>* act_x, int level) const;
   void Replace( t_RT_Elem< T>* oldEle, t_RT_Elem< T>* newEle);
   bool RecursiveInsert( t_RT_Elem< T>*& start, t_RT_Elem< T>* before, t_RT_Elem< T>* data);
   t_RT_Elem< T>* FindGreater( t_RT_Elem< T>* ab) const;
   t_RT_Elem< T>* FindSmaller( t_RT_Elem< T>* ab) const;
   bool RecursiveDelete( t_RT_Elem< T>*& start, t_RT_Elem< T>* del_x);
   void CountWays( t_RT_Elem< T>* act);
   void RecursiveWrite( c_File& fp, t_RT_Elem< T>*& act, bool doDelete);
   t_RT_Elem< T>* RecursiveRead( c_File& fp, int elements, t_RT_Elem< T>* prev);
   void RecursiveDelTree( t_RT_Elem< T>*& act);
   t_RT_Elem< T>* RecursiveCopy( t_RT_Elem< T>* from, t_RT_Elem< T>* prev);

   t_RT_Elem< T>*  mpAct;
   t_RT_Elem< T>*  mpRoot;

}; // t_ReneTree


template< class T> t_ReneTree< T>::t_ReneTree() {

   mEntries  = 0;
   mpRoot    = NULL;
   mpAct     = NULL;
   mInserted = 0;
   mDeleted  = 0;
   mReorgs   = 0;

} // end t_ReneTree< T>::t_ReneTree



/*============================================================================
 Description    : t_ReneTree< T>::t_ReneTree( fromFile)

    Reads a rene-tree from the file 'Filename'.

 Parameter      :
    fromFile: the name of the file to read the tree from.

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_ReneTree< T>::t_ReneTree( c_File& fromFile) {

   mEntries  = 0;
   mpRoot    = NULL;
   mpAct     = NULL;
   mInserted = 0;
   mDeleted  = 0;
   mReorgs   = 0;

   Read( fromFile);

} // end t_ReneTree< T>::t_ReneTree



/*============================================================================
 Description    : t_ReneTree< T>::t_ReneTree( other)

    Copy constructor, copies the complete tree.

 Parameter      :
    other: another t_ReneTree object to copy the data from

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_ReneTree< T>::t_ReneTree( const t_ReneTree& other) {

   mEntries  = other.mEntries;
   mpAct     = NULL;
   mInserted = other.mInserted;
   mDeleted  = other.mDeleted;
   mReorgs   = other.mReorgs;

   mpRoot = RecursiveCopy( other.mpRoot, NULL);

} // end t_ReneTree< T>::t_ReneTree



/*============================================================================
 Description    : t_ReneTree< T>::~t_ReneTree()

    Destructor, deletes the tree contents.

 Parameter      : --

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_ReneTree< T>::~t_ReneTree( void) {

   DeleteAll();

} // end t_ReneTree< T>::~t_ReneTree



/*============================================================================
 Description    : t_ReneTree< T>::Insert( data): Status

    Insert the data in 'data' in the tree.

 Parameter      :
    data: the data to insert in the tree

 Return value   : true when the data could be inserted, false otherwise.
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> bool t_ReneTree< T>::Insert( const T& data) {

   t_RT_Elem< T>*  newEle;
   bool            result = false;


   if ((newEle = new t_RT_Elem< T>( data)) == NULL) {
      fprintf( stderr, "Error: Could not allocate new node!\n");
      exit( EXIT_SUCCESS);
   } // end if

   if (result = RecursiveInsert( mpRoot, NULL, newEle)) {
      mEntries++;
      mInserted++;
   } // end if

   return result;
} // end t_ReneTree< T>::Insert



/*============================================================================
 Description    : t_ReneTree< T>::Delete(): Status

    Deletes the current data in the tree. This means that the data must be
    located before using 'Find' or 'First/Next/Prev/Last'!

 Parameter      : --

 Return value   : true when the data could be deleted, false otherwise.
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> bool t_ReneTree< T>::Delete( void) {

   bool  result = false;


   if (result = RecursiveDelete( mpRoot, mpAct)) {
      // RecursiveDelete only removes the node from the tree, so:
      delete mpAct;
      mpAct = NULL;
      mEntries--;
      mDeleted++;
   } // end if

   return result;
} // end t_ReneTree< T>::Delete



/*============================================================================
 Description    : t_ReneTree< T>::Find( data): dataPtr

    Searches the data in 'data' in the tree and returns a pointer to them if
    found. Subsequently the tree can be scanned using 'Prev/Next' or the
    data deleted using 'Delete'.

 Parameter      :
    data: Pointer to the data buffer

 Return value   : dataPtr: Pointer to the data or NULL if not found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> T* t_ReneTree< T>::Find( const T& data) {

   t_RT_Elem< T>*  act;
   int             relation;


   act = mpRoot;
   while (act != NULL) {
      if (mConstTree) relation = mCompare_c( data, &act->data);
      else relation = mCompare( data, len, &act->data, act->len);

      if (data == act->data) break;

      if (data < act->data) {
         act = act->pLeft;
      } else {
         act = act->pRight;
      } // end if
   } // end while

   mpAct = act;

   if (act != NULL) {
      return &act->data;
   } else {
      return NULL;
   } // end if
} // end t_ReneTree< T>::Find



/*============================================================================
 Description    : t_ReneTree< T>::First(): dataPtr

    Locates the first data in the tree.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> T* t_ReneTree< T>::First( void) {

   t_RT_Elem< T>*  act;


   if (mpRoot == NULL) return NULL;

   for (act = mpRoot; act->pLeft != NULL; act = act->pLeft);

   mpAct = act;

   if (act != NULL) {
      return &act->data;
   } else {
      return NULL;
   } // end if

} // end t_ReneTree< T>::First



/*============================================================================
 Description    : t_ReneTree< T>::Next(): dataPtr

    Locates the next data in the tree. 'First' or 'Find' must have been used
    before.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> T* t_ReneTree< T>::Next( void) {

   t_RT_Elem< T>*  act;
   t_RT_Elem< T>*  last;


   if ((act = mpAct) == NULL) return NULL;

   if (act->pRight != NULL) {
      act = act->pRight;
      while (act->pLeft != NULL) act = act->pLeft;
   } else {
      for (last = act, act = act->pPrev;
           (act != NULL) && (act->pLeft != last);
           last = act, act = act->pPrev);
   } // end if

   mpAct = act;

   if (act != NULL) {
      return &act->data;
   } else {
      return NULL;
   } // end if
} // end t_ReneTree< T>::Next



/*============================================================================
 Description    : t_ReneTree< T>::Prev(): dataPtr

    Locates the previous data in the tree. 'Find' or 'Last' must have been
    used before.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> T* t_ReneTree< T>::Prev( void) {

   t_RT_Elem< T>*  act;
   t_RT_Elem< T>*  last;


   if ((act = mpAct) == NULL) return NULL;

   if (act->pLeft != NULL) {
      act = act->pLeft;
      while (act->pRight != NULL) act = act->pRight;
   } else {
      for (last = act, act = act->pPrev;
           (act != NULL) && (act->pRight != last);
           last = act, act = act->pPrev);
   } // end if

   mpAct = act;

   if (act != NULL) {
      return &act->data;
   } else {
      return NULL;
   } // end if
} // end t_ReneTree< T>::Prev



/*============================================================================
 Description    : t_ReneTree< T>::Last(): dataPtr

    Locates the last data in the tree.

 Parameter      : --

 Return value   : dataPtr: Pointer to the data or NULL if nothing found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> T* t_ReneTree< T>::Last( void) {

   t_RT_Elem< T>*  act;


   if (mpRoot == NULL) return NULL;

   for (act = mpRoot; act->pRight != NULL; act = act->pRight);

   mpAct = act;

   if (act != NULL) {
      return &act->data;
   } else {
      return NULL;
   } // end if
} // end t_ReneTree< T>::Last



/*============================================================================
 Description    : t_ReneTree< T>::Info( longPath, average): Status

    Returns information about the state of the rene-tree.
    longPath = maximum depth of the tree (ideally 2log( elements)
    average  = average path length = sum of all path-lengths / elements

 Parameter      :
    longPath: returns the longest path to an element
    average:  returns the average path length

 Return value   : Status: -1 or the number of elements in the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Info( long int& longPath, double& average) {

   int  result = -1;


   if (mpRoot != NULL) {
      mSum      = 0l;
      mLongPath = 0l;
      mWayLen   = 0l;

      result = mEntries;
      CountWays( mpRoot);

      longPath = mLongPath;
      average  = (double) mSum / (double) result;
   } // end if

   return result;
} // end t_ReneTree< T>::Info



/*============================================================================
 Description    : t_ReneTree< T>::Write( toFile, doDelete): Status

    Stores the data of a rene-tree in a the file 'filename'.
    If 'doDelete' is set (true) the tree contents are deleted.
    That's why the address of the pointer to the tree must be passed. After
    deleting the pointer is NULL.

 Parameter      :
    toFile:   the name of the file to store the tree in
    doDelete: true = delete the tree, false = store only

 Return value   : Status: ERROR (-1) or number of data written
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Write( c_File& toFile, bool doDelete) {

   int  written;


   if (mpRoot == NULL) return -1;

   if (!toFile.Opened()) {
      toFile.Open( "wb");
   } // end if

   toFile.Seek( 0);
   written = mEntries;
   toFile.Write( &written, sizeof( written));

   RecursiveWrite( toFile, mpRoot, doDelete);

   toFile.Close();

   return written;
} // end t_ReneTree< T>::Write



/*============================================================================
 Description    : t_ReneTree< T>::Read( fromFile): success

    Reads a rene-tree from the file 'fromFile'. Any data previously stored
    in the tree is deleted.

 Parameter      :
    fromFile: the name of the file to read the tree from.

 Return value   : success: true when the tree could be read, false otherwise
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> bool t_ReneTree< T>::Read( c_File& fromFile) {

   if (!fromFile.Opened()) {
      fromFile.Open( "rb");
   } // end if

   fromFile.Read( &mEntries, sizeof( mEntries));

   mpRoot = RecursiveRead( fromFile, mEntries, NULL);

   fromFile.Close();

   return true;
} // end t_ReneTree< T>::Read



/*============================================================================
 Description    : t_ReneTree< T>::DeleteAll()

    Deletes a rene-tree.

 Parameter      : --

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> void t_ReneTree< T>::DeleteAll( void) {

   if (mpRoot != NULL) {
      RecursiveDelTree( mpRoot);
   } // end if

} // end t_ReneTree< T>::DeleteAll



/*============================================================================
 Description    : t_ReneTree< T>::Entries(): numEntries

    Returns the number of entries in the tree.

 Parameter      : --

 Return value   : numEntries: the number of entries in the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Entries( void) const {
   return mEntries;
} // end t_ReneTree< T>::Entries



/*============================================================================
 Description    : t_ReneTree< T>::Inserted(): numInserted

    Returns the number of entires inserted into the tree. As long as no entry
    is deleted, this equals to the number of entries.

 Parameter      : --

 Return value   : numInserted: the number of entries inserted into the tree
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Inserted( void) const {
   return mInserted;
} // end t_ReneTree< T>::Entries



/*============================================================================
 Description    : t_ReneTree< T>::Deleted(): numDeleted

    Returns the number of entries that were deleted from the tree.

 Parameter      : --

 Return value   : numDeleted: the number of entries that were deleted
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Deleted( void) const {
   return mDeleted;
} // end t_ReneTree< T>::Deleted



/*============================================================================
 Description    : t_ReneTree< T>::Reorgs(): numReorgs

    Returns the number of tree-internal reorganisations.

 Parameter      : --

 Return value   : numReorgs: the number of tree-internal reorganisations
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> int t_ReneTree< T>::Reorgs( void) const {
   return mReorgs;
} // end t_ReneTree< T>::Reorgs



// ===========================================================================
// end of public methods, begin of private methods
// ============================================================================



/*============================================================================
 Description    : t_ReneTree< T>::GetGreater( ab, act_x, level): deleted

    Searches from 'ab' recursive the greatest value. If the value found is
    smaller than 'act_x' it is deleted.

 Parameter      :
    ab:    Pointer to the start node
    act_x: the compare-value as criteria for deleting or not
    level: depth of recursion

 Return value   : deleted: pointer to the deleted data, NULL otherwise
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::GetGreater( t_RT_Elem< T>* ab,
                                                              t_RT_Elem< T>* act_x,
                                                              int level) const {

   t_RT_Elem< T>*  was_deleted = NULL;


   if (ab->pLeft != NULL) {
      if ((was_deleted = GetGreater( ab->pLeft, act_x, 1)) != NULL) {
         // !NULL = was_deleted = Balance korrigieren
         ab->bal++;
      } // end if
   } else {
      // es gibt keinen left mehr, also ist dies der gesuchte Knoten
      if ((act_x == NULL) || (ab->data < act_x->data)) {
         was_deleted = ab;
         // der aktuelle Wert erfuellt die Bedingung
         if (level) {
            ab->pPrev->pLeft = ab->pRight;
         } else {
            ab->pPrev->pRight = ab->pRight;
         } // end if
         if (ab->pRight != NULL) ab->pRight->pPrev = ab->pPrev;
      } // end if
   } // end if

   return was_deleted;
} // end t_ReneTree< T>::GetGreater



/*============================================================================
 Description    : t_ReneTree< T>::GetSmaller( ab, act_x, level): deleted

    Searches from 'ab' recursive the smallest value. If the value found is
    greater than 'act_x' it is deleted.

 Parameter      :
    ab:    Pointer to the start node
    act_x: the compare-value as criteria for deleting or not
    level: depth of recursion

 Return value   : deleted: pointer to the deleted data, NULL otherwise
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::GetSmaller( t_RT_Elem< T>* ab,
                                                              t_RT_Elem< T>* act_x,
                                                              int level) const {

   t_RT_Elem< T>*  was_deleted = NULL;


   if (ab->pRight != NULL) {
      if ((was_deleted = GetSmaller( ab->pRight, act_x, 1)) != NULL) {
         // !NULL = was_deleted = Balance korrigieren
         ab->bal--;
      } // end if
   } else {
      // es gibt keinen right mehr, also ist dies der gesuchte Knoten
      if ((act_x == NULL) || (ab->data >= act_x->data)) {
         was_deleted = ab;
         // der aktuelle Wert erfuellt die Bedingung
         if (level) {
            ab->pPrev->pRight = ab->pLeft;
         } else {
            ab->pPrev->pLeft  = ab->pLeft;
         } // end if
         if (ab->pLeft != NULL) ab->pLeft->pPrev = ab->pPrev;
      } // end if
   } // end if

   return was_deleted;
} // end t_ReneTree< T>::GetSmaller



/*============================================================================
 Description    : t_ReneTree< T>::Replace( oldEle, newEle)

    Unlinks the node 'old' from the tree, replacing it with 'new'.

 Parameter      :
    oldEle: Pointer to the node that is to be unlinked
    newEle: Pointer to the node that is linked in this tree position instead

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> void t_ReneTree< T>::Replace( t_RT_Elem< T>* oldEle,
                                                 t_RT_Elem< T>* newEle) {

   // Pointer des Vorgaengers umhaengen
   if ((newEle->pPrev = oldEle->pPrev) != NULL) {
      if (oldEle->pPrev->pLeft == oldEle) {
         oldEle->pPrev->pLeft = newEle;
      } else {
         oldEle->pPrev->pRight = newEle;
      } // end if
   } else {
      mpRoot = newEle;
   } // end if

   newEle->bal = oldEle->bal;

   // die Pointer der Nachfolger umhaengen
   if ((newEle->pLeft = oldEle->pLeft) != NULL) {
      newEle->pLeft->pPrev = newEle;
   } // end if
   if ((newEle->pRight = oldEle->pRight) != NULL) {
      newEle->pRight->pPrev = newEle;
   } // end if

} // end t_ReneTree< T>::Replace



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveInsert( start, before, data)

    Recursively walks the tree to find the position to insert the data in
    'data'.

 Parameter      :
    start:  start position for inserting
    before: pointer to the previous data
    data:   pointer to the new node

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> bool t_ReneTree< T>::RecursiveInsert( t_RT_Elem< T>*& start,
                                                         t_RT_Elem< T>* before,
                                                         t_RT_Elem< T>* data) {

   t_RT_Elem< T>*  act;
   t_RT_Elem< T>*  found;
   bool            result = false;


   if (start == NULL) {
      start = data;
      data->pLeft = data->pRight = NULL;
      data->pPrev = before;
      data->bal   = 0;
      result = true;
   } else {
      act = start;
      if (data->data == act->data) {
         errno = EEXIST;
         result = -1;
      } else if (data->data > act->data) {
         // es muss rechts eingefuegt werden
         if (act->bal + 1 < 2) {
            if (result = RecursiveInsert( act->pRight, act, data)) {
               act->bal++;
            } // end if
         } else {
            // zuerst umsortieren -> wir suchen den naechstgroesseren
            mReorgs++;
            if ((found = GetGreater( act->pRight, data, 0)) != NULL) {
               // act durch den gefundenen ersetzen
               Replace( act, found);
               if (result = RecursiveInsert( found->pRight, found, data)) {
                  if (result = RecursiveInsert( found->pLeft, found, act)) {
                     found->bal--;
                  } // end if
               } // end if
            } else {
               // der gefundene ist groesser als der neue -> x wird start
               Replace( act, data);
               if (result = RecursiveInsert( data->pLeft, data, act)) {
                  data->bal--;
               } // end if
            } // end if
         } // end if
      } else {
         // es muss links eingefuegt werden
         if (act->bal - 1 > -2) {
            if (result = RecursiveInsert( act->pLeft, act, data)) {
               act->bal--;
            } // end if
         } else {
            // zuerst umsortieren -> wir suchen den naechstkleineren
            mReorgs++;
            if ((found = GetSmaller( act->pLeft, data, 0)) != NULL) {
               // act durch den gefundenen ersetzen
               Replace( act, found);
               if (result = RecursiveInsert( found->pLeft, found, data)) {
                  if (result = RecursiveInsert( found->pRight, found, act)) {
                     found->bal++;
                  } // end if
               } // end if
            } else {
               // der gefundene ist kleiner als der neue -> x wird start
               Replace( act, data);
               if (result = RecursiveInsert( data->pRight, data, act)) {
                  data->bal++;
               } // end if
            } // end if
         } // end if
      } // end if
   } // end if

   return result;
} // end t_ReneTree< T>::RecursiveInsert



/*============================================================================
 Description    : t_ReneTree< T>::FindGreater( ab): found

    Searches the greatest value starting from 'ab'.

 Parameter      :
    ab: Pointer to the start node

 Return value   : found: Pointer to the data found
 -----------------------------------------------------------------------------
 Date           Comment
 31.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::FindGreater( t_RT_Elem< T>* ab) const {

   t_RT_Elem< T>*  found;


   for (found = ab; found->pLeft != NULL; found = found->pLeft);

   return found;
} // end t_ReneTree< T>::FindGreater



/*============================================================================
 Description    : t_ReneTree< T>::FindSmaller( ab): found

    Searches the smallest value starting from 'ab'.

 Parameter      :
    ab: Pointer to the start node

 Return value   : found: Pointer to the data found
 -----------------------------------------------------------------------------
 Date           Comment
 01.01.2003     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::FindSmaller( t_RT_Elem< T>* ab) const {

   t_RT_Elem< T>*  found;


   for (found = ab; found->pRight != NULL; found = found->pRight);

   return found;
} // end t_ReneTree< T>::FindSmaller



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveDelete( start, del_x): deleted

    Unlinks the node pointed to by 'del_x' from the tree.
    The node itself is not deleted.

 Parameter      :
    start: Start of the subtree
    del_x: the node that is unlinked from the tree

 Return value   : deleted: true when node deleted, false otherwise
 -----------------------------------------------------------------------------
 Date           Comment
 01.01.2003     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> bool t_ReneTree< T>::RecursiveDelete( t_RT_Elem< T>*& start,
                                                         t_RT_Elem< T>* del_x) {

   t_RT_Elem< T>*  found;
   t_RT_Elem< T>*  act;
   bool            result = true;


   if (start == NULL) return false;

   act = start;
   if (act == del_x) {
      // here it is
      if (act->pLeft == act->pRight) {
         // beide sind also NULL: nur den Pointer des Vorgaengers loeschen!
         start = NULL;
      } else if (act->pLeft == NULL) {
         // aktuellen Datensatz aus Liste ausklinken
         act->pRight->pPrev = act->pPrev;
         start = act = act->pRight;
      } else if (act->pRight == NULL) {
         // aktuellen Datensatz aus Liste ausklinken
         act->pLeft->pPrev = act->pPrev;
         start = act = act->pLeft;
      } else {
         // wir haben also einen Knoten mit zwei Nachfolgern:
         // Ersetzen durch geeigneten Wert.
         if (act->bal == -1) {
            // Teilbaum ist linkslastig: suchen kleineren Wert
            found = FindSmaller( act->pLeft);
            if (result = RecursiveDelete( act->pLeft, found)) {
               Replace( act, found);
               found->bal++;
            } // end if
         } else {
            // Teilbaum ist ausgeglichen oder rechtslastig: suchen groesseren
            found = FindGreater( act->pRight);
            if (result = RecursiveDelete( act->pRight, found)) {
               Replace( act, found);
               found->bal--;
            } // end if
         } // end if
      } // end if
   } else {
      if (act->data >= del_x->data) {
         if (act->bal + 1 < 2) {
            if (result = RecursiveDelete( act->pLeft, del_x)) {
               act->bal++;
            } // end if
         } else {
            mReorgs++;
            // wir muessen umsortieren.
            // Dies erreichen wir, indem der naechstgroessere Wert gesucht wird.
            // Dieser Knoten wird geloescht, der Wert in den aktuellen Knoten
            // geschrieben und dessen alter Wert wird wieder eingefuegt.
            // Danach weiterloeschen.
            found = FindGreater( act->pRight);
            if (result = RecursiveDelete( act->pRight, found)) {
               Replace( act, found);
               RecursiveInsert( found->pLeft, found, act);
               if (result = RecursiveDelete( found->pLeft, del_x)) {
                  found->bal--;
               } // end if
            } // end if
         } // end if
      } else {
         if (act->bal - 1 > -2) {
            if (result = RecursiveDelete( act->pRight, del_x)) {
               act->bal--;
            } // end if
         } else {
            mReorgs++;
            // wir muessen umsortieren.
            // Dies erreichen wir, indem der naechstkleinere Wert gesucht wird.
            // Dieser Knoten wird geloescht, der Wert in den aktuellen Knoten
            // geschrieben und dessen alter Wert wird wieder eingefuegt.
            // Danach weiterloeschen.
            found = FindSmaller( act->pLeft);
            if (result = RecursiveDelete( act->pLeft, found)) {
               Replace( act, found);
               RecursiveInsert( found->pRight, found, act);
               if (result = RecursiveDelete( found->pRight, del_x)) {
                  found->bal++;
               } // end if
            } // end if
         } // end if
      } // end if
   } // end if

   return result;
} // end t_ReneTree< T>::RecursiveDelete



/*============================================================================
 Description    : t_ReneTree< T>::CountWays( act)

    Determines the longest path as well as the sum of all path lengths.

 Parameter      :
    act: Pointer to the current data

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 01.01.2003     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> void t_ReneTree< T>::CountWays( t_RT_Elem< T>* act) {

   if (act != NULL) {
      mWayLen++;
      CountWays( act->pLeft);
      if (mWayLen > mLongPath) mLongPath = mWayLen;
      mSum += mWayLen;
      CountWays( act->pRight);
      mWayLen--;
   } // end if

} // end t_ReneTree< T>::CountWays



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveWrite( fp, act, do_delete)

    Helpfunction to store the tree in a file.
    Recursively goes through the tree and stores the current data.

 Parameter      :
    fp:       pointer to the open file
    act:      pointer to the current data
    doDelete: if true the nodes are deleted

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 01.01.2003     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> void t_ReneTree< T>::RecursiveWrite( c_File& fp,
                                                        t_RT_Elem< T>*& act,
                                                        bool doDelete) {

   if (act != NULL) {
      RecursiveWrite( fp, act->pLeft, doDelete);
      fp.Write( &act->data, sizeof( act->data));
      RecursiveWrite( fp, act->pRight, doDelete);
      if (doDelete) {
         delete act;
         act = NULL;
      } // end if
   } // end if

} // end t_ReneTree< T>::RecursiveWrite



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveRead( fp, elements, prev): elePtr

    Helpfunction to read a tree from a file.

 Parameter      :
    fp:       pointer to the open file
    elements: number of data in the following subtree
    prev:     pointer to the previous data

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 01.01.2003     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::RecursiveRead( c_File& fp,
                                                                 int elements,
                                                                 t_RT_Elem< T>* prev) {

   t_RT_Elem< T>*  newEle;
   t_RT_Elem< T>*  left;


   if (elements == 0) {
      newEle = NULL;
   } else {
      if ((newEle = new t_RT_Elem< T>) == NULL) {
         fprintf( stderr, "Error: Could not allocate new node.\n");
         exit( EXIT_SUCCESS);
      } // end if

      newEle->pPrev = prev;
      newEle->pLeft = RecursiveRead( fp, elements / 2, newEle);

      // jetzt kommt mein Datensatz!
      fp.Read( &newEle->data, sizeof( newEle->data));

      newEle->pRight = RecursiveRead( fp, elements - 1 - (elements / 2), newEle);

      // jetzt wo links und rechts gelesen ist koennen wir die Balance setzen
      if (newEle->pLeft == newEle->pRight) {
         newEle->bal = 0;
      } else if ((newEle->pLeft != NULL) && (newEle->pRight == NULL)) {
         newEle->bal = -1;
      } else if ((newEle->pLeft == NULL) && (newEle->pRight != NULL)) {
         newEle->bal = 1;
      } else {
         newEle->bal = bal_mat[ newEle->pLeft->bal + 1][ newEle->pRight->bal + 1];
      } // end if
   } // end if

   return newEle;
} // end t_ReneTree< T>::RecursiveRead



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveDelTree( act)

    Helpfunction to delete a tree.

 Parameter      :
    act: reference of the pointer to the current data

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 06.09.1995     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> void t_ReneTree< T>::RecursiveDelTree( t_RT_Elem< T>*& act) {

   if (act != NULL) {
      RecursiveDelTree( act->pLeft);
      RecursiveDelTree( act->pRight);
      delete act;
      act = NULL;
   } // end if

} // end t_ReneTree< T>::RecursiveDelTree



/*============================================================================
 Description    : t_ReneTree< T>::RecursiveCopy( from, prev): elePtr

    Helpfunction to copy a tree.

 Parameter      :
    from: pointer to the source-tree to copy from
    prev: pointer to the previous data

 Return value   : --
 -----------------------------------------------------------------------------
 Date           Comment
 29.12.2002     --
 -----------------------------------------------------------------------------
 Modifications  :
 Date           Description
 =============================================================================*/
template< class T> t_RT_Elem< T>* t_ReneTree< T>::RecursiveCopy( t_RT_Elem< T>* from,
                                                                 t_RT_Elem< T>* prev) {

   t_RT_Elem< T>*  newEle;


   if ((newEle = new t_RT_Elem< T>( from->data)) == NULL) {
      fprintf( stderr, "Error: Could not allocate new node.\n");
      exit( EXIT_SUCCESS);
   } // end if

   newEle->pPrev  = prev;
   newEle->bal    = from->bal;
   newEle->pLeft  = NULL;
   newEle->pRight = NULL;

   if (from->pLeft != NULL) {
      newEle->pLeft = RecursiveCopy( from->pLeft, newEle);
   } // end if
   if (from->pRight != NULL) {
      newEle->pRight = RecursiveCopy( from->pRight, newEle);
   } // end if

   return newEle;
} // end t_ReneTree< T>::RecursiveCopy


// ========================  END OF t_ReneTree.cpp  ========================

