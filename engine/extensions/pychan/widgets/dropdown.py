# -*- coding: utf-8 -*-

from common import *
from widget import Widget
from listbox import GenericListmodel

class DropDown(Widget):
	"""
	A dropdown or combo box widget for selecting lists of strings.

	New Attributes
	==============

	  - items: A List of strings. This can be treated like an ordinary python list.
	    but only strings are allowed.
	  - selected: The index of the selected item in the list. Starting from C{0} to C{len(items)-1}.
	    A negative value indicates, that no item is selected.
	  - selected_item: The selected string itself, or C{None} - if no string is selected.

	Data
	====
	The selected attribute can be read and set via L{distributeData} and L{collectData}.
	The list items can be set via L{distributeInitialData}.
	"""
	def __init__(self,items=[],**kwargs):
		self._items = GenericListmodel(*items)
		self.real_widget = fife.DropDown(self._items)
		super(DropDown,self).__init__(**kwargs)

		# Prepare Data collection framework
		self.accepts_initial_data = True
		self._realSetInitialData = self._setItems

		self.accepts_data = True
		self._realSetData = self._setSelected
		self._realGetData = self._getSelected

	def resizeToContent(self,recurse=True):
		# We append a minimum value, so max() does not bail out,
		# if no items are in the list
		_item_widths = map(self.real_font.getWidth,map(str,self._items)) + [self.real_font.getHeight()]
		max_w = max(_item_widths)
		self.width = max_w
		self.height = (self.real_font.getHeight() + 2)

	def _getItems(self): return self._items
	def _setItems(self,items):
		# Note we cannot use real_widget.setListModel
		# for some reason ???

		# Also self assignment can kill you
		if id(items) != id(self._items):
			self._items.clear()
			self._items.extend(items)
	items = property(_getItems,_setItems)

	def _getSelected(self): return self.real_widget.getSelected()
	def _setSelected(self,index): self.real_widget.setSelected(index)
	selected = property(_getSelected,_setSelected)
	def _getSelectedItem(self):
		if 0 <= self.selected < len(self._items):
			return self._items[self.selected]
		return None
	selected_item = property(_getSelectedItem)
