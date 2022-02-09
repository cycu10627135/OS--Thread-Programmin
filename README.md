# Thread-Programmin
假設有一個檔案內有若干個(N個)數目字(至少多於1萬,最多不超過100萬),請寫一個java thread的程式,能夠將該些數目字切成k份(k由使用者自訂),並由K個threads分別進行Bubble Sort之後,
再由k-1個threads作Merge Sort,以完成這些數目字之排序.同時顯示CPU執行之時間.本程式需完成下列事項:

1. 將N個數目字直接作Bubble Sort,並顯示CPU執行之時間。  
2. 將N個數目字切成k份,並由K個threads分別進行Bubble Sort之後,再由k-1個threads作Merge Sort,同時顯示CPU執行之時間。  
3. 將N個數目字切成k份,並由K個Processes分別進行Bubble Sort之後,再由k-1個Processes作Merge Sort,同時顯示CPU執行之時間。  
4. 將N個數目字切成k份,並由K個Processes分別進行Bubble Sort之後,再由k-1個Processes作Merge Sort,同時顯示CPU執行之時間。  

完成後，寫成檔案，報告各項結果以及差異。  
